#include <iostream>
#include <stdio.h>
#include <omp.h>
int main()
{
	int num;
	#pragma omp parallel num_threads(4) private(num) 
	{
		num = omp_get_thread_num();
		printf("Before the directive single num=%d \n", num);
#pragma omp barrier
#pragma omp single copyprivate(num)
		{
			printf("Enter an integer: ");
			scanf("%d", &num);
		}
		printf("After the directive single num=%d \n", num);
	}
}
