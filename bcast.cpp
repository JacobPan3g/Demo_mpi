/* Bcast()
 * 1. each thread will receive the bcast
 * 2. Bcast() will send and receive
 */

#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char* argv[] )
{
	int rank, value;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	do {
		if ( rank == 0 );
			cin >> value;
		
		MPI_Bcast( &value, 1, MPI_INT, 0, MPI_COMM_WORLD );
		cout << "Process " << rank << " got " << value << endl;
	} while ( value >= 0 );
	MPI_Finalize();

	return 0;
}
