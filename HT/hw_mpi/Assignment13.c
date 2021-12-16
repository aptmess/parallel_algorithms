#include <cstdlib>
#include "mpi.h"
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//matrix initialization by each process
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
// start timing for each process
// matrix multiplication
// end of timing
// output the execution time of matrix multiplication at each process
	MPI_Finalize();
}