#include <stdio.h>

int main()
{
	printf("Serial block 1\n");
#pragma omp parallel num_threads(5)
	{
		printf("Parallel block\n");
	}
	printf("Serial block 2\n");
}
