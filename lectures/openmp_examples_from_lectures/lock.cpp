#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int n; 
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel private (n)
	{
		n = omp_get_thread_num();
		omp_set_lock(&lock);
		printf("Start of locked section by thread %d\n", n);
		sleep(3);
		printf("Stop of locked section by thread %d\n", n);
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
	return 0;
}
