#include <stdio.h>
#include <omp.h>

int main()
{
	
	int n;
#pragma omp parallel private(n)
	{
		n = 1;
#pragma omp master
		{
			n = 2;
		}
		printf("The first value of the n thread %d: %d\n", omp_get_thread_num(),n);
#pragma omp barrier
#pragma omp master
		{
			n = 3;
		}
		printf("The second value of the n thread %d: %d\n", omp_get_thread_num(),  n);
	}
	return 0;
}
