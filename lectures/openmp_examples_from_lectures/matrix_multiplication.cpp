#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// The function of allocating memory for a two-dimensional array
double** malloc_array(long int n)
{
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
	return matrix;
}

// Memory free function
void free_array(double** matrix,long int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

// The function of initializing a matrix with random numbers from [0,1]
void rand_init_matrix(double** matrix,long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = rand() / RAND_MAX;
}

// Matrix zeroing function
void zero_init_matrix(double** matrix, long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0.0 ;
}

int main()
{
	const long int N = 1000;
	double** A, **B, **C;

// Memory allocation for matrices A, B, C
	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);

// Initialization of matrices
	rand_init_matrix(A, N);
	rand_init_matrix(B, N);
	zero_init_matrix(C, N);
	clock_t t;
	
// Matrix multiplication with cycle order ijk
	t = clock();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
	t = clock() - t;
	cout << "Time ijk loops is " << t / CLOCKS_PER_SEC << " seconds" <<  endl;

// Matrix multiplication with cycle order jki
	zero_init_matrix(C, N);
	t = clock();
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				C[i][j] += A[i][k] * B[k][j];
	t = clock() - t;
	cout << "Time jki loops is " << t / CLOCKS_PER_SEC << " seconds" <<  endl;

// Matrix multiplication with cycle order ikj
	zero_init_matrix(C, N);
	t = clock();
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				C[i][j] += A[i][k] * B[k][j];
	t = clock() - t;
	cout << "Time ikj loops is " << t / CLOCKS_PER_SEC << " seconds" << endl;
	
// Freeing memory occupied by matrices A, B, C
	free_array(A, N);
	free_array(B, N);
	free_array(C, N);

	return 0;
}
