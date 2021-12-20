#include <mpi.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

static int const root = 0;

using namespace std;

int sum_of_array(int x[], int n) 
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum = sum + x[i];
	
	return sum;
}


int parallel_sum_reduce(int x[], int batch_size) 
{
	/*
	parallel sum with MPI_SUM as a reduce operation
	*/
	int local_sum, full_sum = 0;
	int sum_of_array(int x[], int m);
	
	local_sum = sum_of_array(x, batch_size);
	
	MPI_Reduce(&local_sum, &full_sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	
	return full_sum;
}


int parallel_sum_doubling(int x[], int batch_size, int rank, int n, MPI_Status status) 
{
	/*
	parallel sum with MPI_SUM as a double operation
	*/
	int full_sum, dummy_reciever, u, child;
	int sum_of_array(int x[], int m);
	
	full_sum = sum_of_array(x, batch_size);

	for (int p = 2; p <= n; p *= 2)
	{
		u = rank % p;
		child = rank + p / 2;
		if (u == 0 & child < n)
		{
			MPI_Recv(&dummy_reciever, 1, MPI_INT, child, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			full_sum += dummy_reciever;
		}
		else
		{
			MPI_Send(&full_sum, 1, MPI_INT, rank - u, root, MPI_COMM_WORLD);
		}
	}

	
	return full_sum;
}


int split_data_by_processes(int arr[], int batch[], int batch_size)
{
	/*
	splitting arr between each process by batches with length=batch_size
	*/
	MPI_Scatter(arr, batch_size, MPI_INT, batch, batch_size, MPI_INT, root, MPI_COMM_WORLD);
	return 0;
}


int main(int argc, char* argv[])
{
	int length_array = atoi(argv[1]);
	string double_or_reduce = argv[2];
	
	MPI_Init(&argc, &argv);

	int rank, n, batch_size, full_sum;
	double start_time, end_time;
	int *a;

	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;

	batch_size = length_array / n;

	if (rank == root)
	{
		a = new int[length_array]();
		for (int i = 0; i < length_array; i++) a[i] = 1;	
	}

	int *batch = new int[batch_size]();

	if (rank == root) start_time = MPI_Wtime();

	split_data_by_processes(a, batch, batch_size);

	if (double_or_reduce == "double")
	{
		full_sum = parallel_sum_doubling(batch, batch_size, rank, n, status);
	}
	else if (double_or_reduce == "reduce")
	{

		full_sum = parallel_sum_reduce(batch, batch_size);
	}

	if (rank == root)
	{	
		end_time = MPI_Wtime();
		cout << "process " << rank ;
		cout << ": variant=" << double_or_reduce;
		cout << " sum=" << full_sum;
		cout << ", execution time=" << (end_time - start_time);
		cout << '\n' << endl;
	}

	MPI_Finalize();
	return 0;
}