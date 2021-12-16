#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
{
	printf("Message 1\n");
	printf("Message\n");
#pragma omp barrier
	printf("Message 3\n");
}
}
