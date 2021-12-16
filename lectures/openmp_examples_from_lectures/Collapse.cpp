#include <stdio.h>
#include "omp.h"
#include <iostream>
int main()
{
	int j, k, jlast, klast;
#pragma omp parallel num_threads(2)
	{
#pragma omp for collapse(2) lastprivate(jlast, klast)
		for (k = 1; k <= 3; k++)
			for (j = 1; j <= 3; j++)
			{
				printf("Thread %d k=%d j=%d \n", omp_get_thread_num(), k, j);
				jlast = j;
				klast = k;
			}
#pragma omp single
		printf("klast=%d jlast=%d\n", klast, jlast);
	}
}



