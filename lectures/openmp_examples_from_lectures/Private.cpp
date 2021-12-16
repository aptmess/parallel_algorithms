#include <stdio.h>
#include <omp.h>

int main()
{
	int n = 1;
	
	printf("n in sequential area (start): %d\n", n);

#pragma omp parallel private(n) num_threads(4)
	{
		printf("The value of n in the thread (at the input): %d\n", n);
	
		n = omp_get_thread_num(); // We assign n the number of the current thread
		printf("The value of n in the thread (at the output): %d\n", n);

	}
	printf("n in sequential area (end): %d\n", n);
	return 0;
}
