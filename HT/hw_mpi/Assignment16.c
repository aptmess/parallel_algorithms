#include <mpi.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int rank_split = atoi(argv[1]);
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) cout << "rank % " << rank_split << '\n' << endl;
	MPI_Comm_split(MPI_COMM_WORLD, rank % rank_split, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);

	//Display rank and rank1

	cout << "rank=" << rank << ", rank1=" << rank1 << " group=" << rank % rank_split << endl;

	MPI_Comm_free(&comm_revs);
	MPI_Finalize();
}