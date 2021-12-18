#include <stdio.h>
#include "mpi.h"
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i;
	int message[4];
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout << "Start main process " << rank << endl;
		for (i = 1; i < n; i++) 
		{

			MPI_Recv(&message[0], 4, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Print numbers from process " << i << ": "; 
			for (int j = 0; j < 4; j++)
			{
				cout << message[j] << ' ';
			}
			cout << endl;
		}
	}
	else 
	{
		srand(time(NULL) + rank);
		int sending[4];
		for (int i = 0; i < 4; i++)
		{
			sending[i] = 1 + rand() % 20;
		}

		MPI_Send(&sending[0], 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}