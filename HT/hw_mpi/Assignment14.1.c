#include <stdio.h>
#include "mpi.h"
#include <iostream>
#define n 1000

using namespace std;

void maximum(void *inputBuffer, void *outputBuffer, int *len, MPI_Datatype *type) {
	int* input = (int*)inputBuffer;
	int* output = (int*)outputBuffer;
	for (int i = 0; i < *len; i++)
		if (input[i] >= output[i]) output[i] = input[i];
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	int b_check[n];
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++) a[i] = i + rank + 1;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&maximum, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	MPI_Reduce(a, b_check, n, MPI_INT, MPI_MAX , 0, MPI_COMM_WORLD);
	if (rank == 0) 
	{
		printf("b[0] = %d\n", b[0]);
		printf("b_check[0] = %d\n", b[0]);
		int temp = 0;
		for (int i = 0; i < n; i++)
		{
			if (b[i] != b_check[i])
			{
				cout << "Wrong results of functions maximum and MPI_MAX" << endl;
				break;
			}
			else
			{
				temp += 1;
			}
		}
		if (temp == n) 
		{
			cout << "Result of functions maximum and MPI_MAX are correct" << endl;
		}
		
	}
	MPI_Finalize();
}