#include <mpi.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int matrix_size = atoi(argv[1]);
	int rank, size;
	MPI_Init(&argc, &argv);
	
	double start_time, end_time;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//matrix initialization by each process

	int A[matrix_size][matrix_size], B[matrix_size][matrix_size], C[matrix_size][matrix_size];

	for (int i = 0; i < matrix_size; i++)
	{
        for (int j = 0; j < matrix_size; j++)
        {
            A[i][j] = 1 + rand() % 10;
            B[i][j] = 1 + rand() % 10;
            C[i][j] = 0;
        }
     }
    
	
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization

	// start timing for each process

	start_time = MPI_Wtime();
	
	// matrix multiplication

	for (int i = 0; i < matrix_size; i++) {
	    for (int j = 0; j < matrix_size; j++) {
	        for (int k = 0; k < matrix_size; k++) {
	            C[i][j] += A[i][k] * B[k][j];
	        }
	    }
	}
	
	// end of timing

	end_time = MPI_Wtime();
	
	// output the execution time of matrix multiplication at each process
	
	cout << "process " << rank ;
	cout << ", execution time=" << (end_time - start_time);
	cout << '\n' << endl;
	MPI_Finalize();
}