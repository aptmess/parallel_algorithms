#include <iostream>
#include "omp.h"
#include <string>

using namespace std;
int main()
{
	string hw = "Hello, world\n";
#pragma omp parallel num_threads(10)
{
	cout << hw;
}
	return 0;
}
