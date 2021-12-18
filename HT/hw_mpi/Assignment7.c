//Reference to https://edoras.sdsu.edu/~mthomas/sp17.605/lectures/MPI-VectorOps.pdf

#include "mpi.h"
#include <ctime>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int serial_dot(int x[], int y[], int n) 
{
	/*
	serial product of two arrays

	a . b = Sum[a[i] * b[i], {i, 1, n}] = a1 * b1 + ... + an * bn;

	*/
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum = sum + x[i] * y[i];
	
	return sum;
} 

int parallel_dot(int x[], int y[], int batch_size, int root) 
{
	/*
	parallel dot with MPI_SUM as a reduce operation

	MPI_Reduce(
		sbuf - adress of start buffer for arguments
		OUT rbuf - adress of start buffer for results
		count - the amount of arguments for each process
		datatype - type of argument
		op - identifier of reduce operation
		root - main process which will take the result
		comm - communicator
	)
	*/
	int local_dot, full_dot = 0;
	int serial_dot(int x[], int y[], int m);
	
	local_dot = serial_dot(x, y, batch_size);
	
	MPI_Reduce(&local_dot, &full_dot, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	
	return full_dot;
}


int split_data_by_processes(int arr[], int batch[], int batch_size, int root)
{
	/*
	splitting arr between each process by batches with length=batch_size

	MPI_Scatter(
		sbuf - adress of start buffer for arguments in sending message
		scount - amount of elements in sending message
		stype - type of sending message
		OUT rbuf - adress of start buffer for requesting message
		rcount - amount of elements in requesting message
		rtype - type of elements in requesting message
		source - number of process, where data is collecting
		comm - communicator
	)
	*/
	MPI_Scatter(arr, batch_size, MPI_INT, batch, batch_size, MPI_INT, root, MPI_COMM_WORLD);
	return 0;
}

int main(int argc, char* argv[])
{
	int length_array = atoi(argv[1]);
	const int root = 0;

	MPI_Init(&argc, &argv);

	int rank, n, batch_size, dot;
	int *first_array, *second_array;

	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	batch_size = length_array / n;

	if (rank == root)
	{
		first_array = new int[length_array]();
		second_array = new int[length_array]();
		for (int i = 0; i < length_array; i++)
		{
			first_array[i] = 1;
			second_array[i] = 1;
		}
		if (length_array < 20)
		{
			for (int i = 0; i < length_array; i++)
			{
				cout << first_array[i] << ' ';
			}
			cout << endl;

			for (int i = 0; i < length_array; i++)
			{
				cout << second_array[i] << ' ';
			}
			cout << endl;
			}	
		
	}

	int *first_batch = new int[batch_size]();
	int *second_batch = new int[batch_size]();
	split_data_by_processes(first_array, first_batch, batch_size, root);
	split_data_by_processes(second_array, second_batch, batch_size, root);
	dot = parallel_dot(first_batch, second_batch, batch_size, root);

	if (rank == root)
	{
		cout << "sum=" << dot << endl;
		cout << "equal with array size: " << (length_array == dot) << endl;
	}

	MPI_Finalize();
	return 0;
}