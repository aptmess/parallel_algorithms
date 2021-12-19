#include <mpi.h>
#include <iostream>
#include <stdexcept>

using namespace std;

static int const root = 0;
static int const N = 10;

void FactoryMessage(
	string variant, 
	int to_home_sent, 
	int len, 
	int *msg, 
	MPI_Status status
)
{
	double start_time, end_time, T, R, s;
	int L = len * sizeof(int);

	start_time = MPI_Wtime();
	for (int i = 0; i < N; i++)
		if (variant == "send")
		{
			MPI_Send(msg, len, MPI_INT, to_home_sent, root, MPI_COMM_WORLD);
		}
		else if (variant == "recv")
		{
			MPI_Recv(msg, len, MPI_INT, to_home_sent, root, MPI_COMM_WORLD, &status);
		}
	end_time = MPI_Wtime();

	T = (end_time - start_time) * 1000000;
	R = 2 * L * N / T / 1024 / 1024;
	s = T / 2 / N;

	if (variant == "send")
	{
		cout << "rank=" << (to_home_sent ^ 1);
		cout << " len=" << len;
		cout << " L(bytes)=" << L;
		cout << " T(us)=" << T;
		cout << " R[bandwidth](MB/s)=" << R;
		cout << " s[latency](us)=" << s;
		cout << '\n' << endl; 
	}
}


int main(int argc, char **argv)
{
	int rank, n;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int *msg;

	if (n != 2)
	{
		throw invalid_argument( "Only 2 processes is acceptable" );
	}

	for (int len = 1; len <= 1000000; len *= 10)
	{
		msg = new int[len]();
		if (rank == 0)
		{
			for (int i = 0; i < len; i++) 
			{
				msg[i] = 1;
			}

			FactoryMessage("send", 1, len, msg, status);
			FactoryMessage("recv", 1, len, msg, status);
		}
		else if (rank == 1)
		{
			FactoryMessage("recv", 0, len, msg, status);
			FactoryMessage("send", 0, len, msg, status);
		}
		delete[] msg;
	}

	MPI_Finalize();
	return 0;
}