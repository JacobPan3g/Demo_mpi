/* Parallel
 * 1. master-slave model
 * 2. compat for too many threads and too litte threads
 */

#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char *argv[] )
{
	const int sz = 5;
	const int master = 0;

	int rank, numprocs;
	int numsent;
	int A[sz][sz], b[sz], c[sz], buffer[sz];
	//int ans, row;
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &numprocs );

	if ( master == rank ) {
		
		// stop the more thread
		if ( numprocs > sz+1 ) {
			//cout << "Too many Threads" << endl;
			for ( int i = sz+1; i < numprocs; i++ )
				MPI_Send( 0, 0, MPI_INT, i, 0, MPI_COMM_WORLD );
		}

		// init
		for ( int i = 0; i < sz; i++ ) {
			b[i] = 1;
			for ( int j = 0; j < sz; j++ )
				A[i][j] = i;
		}
		numsent = 0;

		// send b
		MPI_Bcast( b, sz, MPI_INT, master, MPI_COMM_WORLD );

		// send a each line
		for ( int i = 0; i < (numprocs-1<sz?numprocs-1:sz); i++ ) {
			MPI_Send( A[i], sz, MPI_INT, i+1, i+1, MPI_COMM_WORLD );
			numsent++;
		}


		// recived the result from each thread
		int ans;
		int sender, idx;
		for ( int i = 0; i < sz; i++ ) {
			MPI_Recv( &ans, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			sender = status.MPI_SOURCE;
			idx = status.MPI_TAG;
			c[idx-1] = ans;

			//cout << sender << " " << ans << endl;

			// if not finish send
			if ( numsent < sz ) {
				MPI_Send( A[numsent], sz, MPI_INT, sender, numsent+1, MPI_COMM_WORLD );
				numsent++;
			}
			else	// stop the thread
				MPI_Send( 0, 0, MPI_INT, sender, 0, MPI_COMM_WORLD );
		}

		// the result
		cout << "The result: ";
		for ( int j = 0; j < sz; j++ ) cout << c[j] << " ";
		cout << endl;
	}

	// not master thread
	else {
		// receive b
		MPI_Bcast( b, sz, MPI_INT, master, MPI_COMM_WORLD );
		
		// loop for receiving the line of A
		int buf[sz];
		while(1) {
			MPI_Recv( buf, sz, MPI_INT, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
		
			if ( status.MPI_TAG != master ) {
				int row = status.MPI_TAG;
				int ans = 0;
				for ( int i = 0; i < sz; i++ ) ans += buf[i]*b[i];
				MPI_Send( &ans, 1, MPI_INT, master, row, MPI_COMM_WORLD );
				
				//cout << "Process " << rank << " got: ";
				//for ( int i = 0; i < sz; i++ ) cout << b[i] << " ";
				//cout << " ";
				//for ( int i = 0; i < sz; i++ ) cout << buf[i] << " ";
				//cout << " ";
				//cout << ans << endl; 
			}
			else 
				break;	// finish this thread
		}
	}

	MPI_Finalize();
	return 0;
}
