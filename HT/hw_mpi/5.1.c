#include <stdio.h>
#include "mpi.h"
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, len;
	char *name = new char;
	double time_start, time_finish;
	int message[5];
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &len);
	time_start = MPI_Wtime();
	if (rank == 0)
	{
		cout << "Start main process " << rank << endl;
		for (i = 1; i < n; i++) 
		{

			MPI_Recv(&message[0], 5, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Print numbers from process " << message[4] << ": "; 
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
		int sending[5];
		for (int i = 0; i < 4; i++)
		{
			sending[i] = 1 + rand() % 20;
		}
		sending[4] = rank;

		MPI_Send(&sending[0], 5, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	time_finish = MPI_Wtime();
	cout << "processor " << name << ", process " << rank << " time = " << time_finish - time_start << endl;
	MPI_Finalize();
	return 0;
}