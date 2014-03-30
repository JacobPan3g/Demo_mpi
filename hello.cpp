#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argv, char* argc[] ) 
{
	MPI_Init( &argv, &argc );
	cout << "Hello World!" << endl;
	//MPI_Barrier( MPI_COMM_WORLD );
	MPI_Finalize();
	
	//cout << "test" << endl;
	return 0;
}


