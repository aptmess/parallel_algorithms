#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
	int i;
#pragma omp parallel private(i) num_threads(4)
	{
//#pragma omp for schedule (static, 6)
#pragma omp for schedule (dynamic, 6)
//#pragma omp for schedule (guided, 6)
		for (i = 0; i<200; i++)
		{
			printf("Thread %d performed iteration %d\n", omp_get_thread_num(), i);
			sleep(2); 
		}
	}
}
