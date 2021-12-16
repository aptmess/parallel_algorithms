#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int max(int arr[], int len, int threads)
{
    int maximum = arr[0];
    #pragma omp parallel for num_threads(threads) reduction(max:maximum) // user max reduction with for
    for (int i = 0; i < len; i++)
    {
        maximum = maximum > arr[i] ? maximum : arr[i];
    }
    return maximum;
}

int* generate_array(int len)
{
    srand(time(NULL)); // new generation
    int* arr = new int[len];
    for (long int i=0; i < len; i++)
    {
        arr[i] = 1 + rand() % len + int(len * 0.4);
    }
    if (len <= 20)
    {
        for (long int i = 0; i < len; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }
    return arr;
}


int main(int argc, char* argv[])
{
    int len = atoi(argv[1]);
    int* arr = generate_array(len);
    for (int num_threads = 1; num_threads <=10; num_threads++)
    {
        double time = omp_get_wtime();
        int maximum = max(arr, len, num_threads);
        printf("max value is %d\ntakes %f seconds with %d threads\n",
                maximum, omp_get_wtime() - time, num_threads);
    }
    delete [] arr;
    return 0;
}

