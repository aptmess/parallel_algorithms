#include <stdio.h>
#include <omp.h>

int main()
{
	omp_set_num_threads(2);
#pragma omp parallel num_threads(3)
	{
		printf("parallel block 1\n");
	}
#pragma omp parallel
	{
		printf("parallel block 2\n");
	}
	return 0;
}
