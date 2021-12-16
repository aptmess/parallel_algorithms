#include <stdio.h>
#include <omp.h>

int main()
{
	int n = 1;
	int i = 0;
	int a;
	printf("The value of n at the beginning: %d\n", a);
#pragma omp parallel for private(i) lastprivate(a) num_threads(5)
	for(i=0;i<5;i++)
		{
			a=i+1;
			n = omp_get_thread_num(); //  assign the variable n to the sequence number of the thread 
			printf("The value of a in the thread %d\n: %d\n",a,n);
		}
printf("The value of a at the end: %d\n", a);
}
