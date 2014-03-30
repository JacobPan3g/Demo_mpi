/* Communication
 * 1. MPI_Recv() will wait unitl reciving the msg, if 3 thread run will be a dead loop. 
 *
 */

#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char *argv[] )
{
	int rank;
	char msg[20];
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	if ( 0 == rank ) {
		strcpy( msg, "Hello, process 1" );
		MPI_Send( msg, strlen(msg)+1, MPI_CHAR, 1, 99, MPI_COMM_WORLD );
	}
	else {
		MPI_Recv( msg, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status );
		cout << "received: " << msg << endl;
	}

	MPI_Finalize();
	return 0;
}
