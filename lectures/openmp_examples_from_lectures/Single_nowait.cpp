#include <iostream>
#include <stdio.h>
#include <omp.h>
int main()
{
	double k = 0;
#pragma omp parallel num_threads(4) firstprivate(k)
	{
		printf("Before single without nowait \n");
#pragma omp single
		{
			// This loop is added so that the thread can do some work.
			for (int i = 0; i < 100000; i++)
			{
				k += (double)i / (i + 1);
			}
			printf("In single directive\n");
		}
		printf("After the single directive without nowait. This message will never be earlier than the previous ones. k = %f \n",k);

#pragma omp barrier // This directive synchronizes threads

		printf("Before single directive with nowait \n");
#pragma omp single nowait
		{
			// his loop is added so that the thread can do some work.
			for (int i = 0; i < 100000; i++)
			{
				k += (double)i / (i + 1);
			}
			printf("In single directive\n");
		}
		printf("After the single directive with nowait. This message may be earlier than the previous ones. k =  %f \n", k);
	}
	return 0;
}
