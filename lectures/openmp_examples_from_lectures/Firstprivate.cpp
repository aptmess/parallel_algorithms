#include <stdio.h>
#include <omp.h>

int main()
{
	int n = 1;

	printf("The value of n at the beginning: %d\n", n);
#pragma omp parallel firstprivate(n)
	{
		printf("The value of n in the thread (at the input): %d\n", n);
		n = n + omp_get_thread_num(); //  assign the variable n to the sequence number of the thread 
		printf("The value of n in the thread (at the output): %d\n", n);
	}
	printf("The value of n at the end: %d\n", n);
}
