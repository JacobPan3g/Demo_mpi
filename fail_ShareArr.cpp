#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char *argv[] )
{
	int data[10];

	int rank, size;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	int stp = 10 / (size-1);
	int b = rank * stp;
	int e = (rank+1) * stp;
	//for ( int i = b; i < e && i < 10; i++ ) {
	//	data[i] = rank;
	//}

	//cout << rank << " " << b << endl;	
	//cout << rank << " " << e << endl;	

	
	MPI_Barrier( MPI_COMM_WORLD );
	if ( rank == 0 )
		for ( int i = 0; i < 10; i++ )
			cout << data[i] << endl;


	MPI_Finalize();

	//cout << endl;

	return 0;
}
