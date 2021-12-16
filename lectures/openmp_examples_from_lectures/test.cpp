#include <iostream>
#include <omp.h>

using std::cout;
using std::endl;

int
main() {
  double x = omp_get_wtime();

  cout << x << endl;
}
