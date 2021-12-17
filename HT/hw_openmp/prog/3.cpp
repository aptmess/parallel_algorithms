#include <iostream>
#include <time.h>
#include <cstdlib>
#include <omp.h>
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
			matrix[i][j] = 1 + rand() % 1000;
}

// Matrix zeroing function
void zero_init_matrix(double** matrix, long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0.0 ;
}


int main(int argc, char* argv[])
{
	const long int N = atoi(argv[1]);
	double** A, **B, **C;
	
	// Memory allocation for matrices A, B, C
	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);

	// Initialization of matrices
	rand_init_matrix(A, N);
	rand_init_matrix(B, N);
	
	double** time_matrix = new double*[6];
	for(int i = 0; i < 6; ++i)
	{
		time_matrix[i] = new double[10];
	}

	for (int threads = 1; threads <=10; threads++)
	{
		// Matrix multiplication with cycle order ijk
		zero_init_matrix(C, N);
		double time = omp_get_wtime();
		#pragma omp parallel for num_threads(threads)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[0][threads - 1] = omp_get_wtime() - time;
		// Matrix multiplication with cycle order ikj
		zero_init_matrix(C, N);
		time = omp_get_wtime();
		#pragma omp parallel for num_threads(threads)
		for (int i = 0; i < N; i++)
			for (int k = 0; k < N; k++)
				for (int j = 0; j < N; j++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[1][threads - 1] = omp_get_wtime() - time;
		
		// Matrix multiplication with cycle order jik
		zero_init_matrix(C, N);
		time = omp_get_wtime();
		#pragma omp parallel for
		for (int j = 0; j < N; j++)
			for (int i = 0; i < N; i++)
				for (int k = 0; k < N; k++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[2][threads - 1] = omp_get_wtime() - time;

		// Matrix multiplication with cycle order jki
		zero_init_matrix(C, N);
		time = omp_get_wtime();
		#pragma omp parallel for
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				for (int i = 0; i < N; i++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[3][threads - 1] = omp_get_wtime() - time;
		
		// Matrix multiplication with cycle order kij
		zero_init_matrix(C, N);
		time = omp_get_wtime();
		#pragma omp parallel for
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[4][threads - 1] = omp_get_wtime() - time;
		
		// Matrix multiplication with cycle order kji
		zero_init_matrix(C, N);
		time = omp_get_wtime();
		#pragma omp parallel for
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				for (int i = 0; i < N; i++)
					C[i][j] += A[i][k] * B[k][j];
		time_matrix[5][threads - 1] = omp_get_wtime() - time;
	}
	
	cout << "--------------------------------------------time matrix----------------------------------------" << endl; 
	cout << "      1        2        3        4        5        6        7        8        9        10       " << endl; 
	cout << "-----------------------------------------------------------------------------------------------" << endl; 
	const char *row[6] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};
    for (int i = 0; i < 6; i++) 
	{
		printf("%s | ", row[i]);
		for (int j = 0; j < 10; j++) 
		{
			printf("%.6f ", time_matrix[i][j]); 
		}
		cout << endl;
    }
	
	cout << "\n------------------------------------------efficiency matrix----------------------------------" << endl; 
	cout << "      1        2        3        4        5        6        7        8        9        10       " << endl; 
	cout << "-----------------------------------------------------------------------------------------------" << endl; 
    for (int i = 0; i < 6; i++) 
	{
		printf("%s | ", row[i]);
		for (int j = 0; j < 10; j++) 
		{
			printf("%.6f ", time_matrix[i][0] / time_matrix[i][j]);
		}
		cout << endl;
    }

	// Freeing memory occupied by matrices A, B, C
	free_array(A, N);
	free_array(B, N);
	free_array(C, N);

	return 0;
}
