#include <stdio.h>
#include <omp.h>

int main()
{
	int n;
	omp_set_nested(1);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp parallel
		{
			printf("part 1, thread %d - %d\n", n,
				omp_get_thread_num());
		}
	}
	omp_set_nested(0);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp parallel
		{
			printf("part 2, thread %d - %d\n", n,
				omp_get_thread_num());
		}
	}
	return 0;
}
