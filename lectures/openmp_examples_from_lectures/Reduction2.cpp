#include <iostream>
#include "omp.h"
#include <string>

using namespace std;
int main()
{
	int x = 0;
#pragma omp parallel reduction(*:x) num_threads(30)
	{
		int n = omp_get_thread_num(); 
		x += n;
	}
	cout << "x = " << x << endl;
	return 0;
}
