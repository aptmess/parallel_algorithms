#include <stdio.h>
#include <omp.h>

int main()
{
	int i, n;
#pragma omp parallel private (i, n)
	{
		n = omp_get_thread_num();
#pragma omp for ordered
		for (i = 0; i<5; i++)
		{
#pragma omp ordered
		{
			printf("ordered: Thread %d, iteration %d\n", n, i);
		}
		}
	}
}

