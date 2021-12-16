#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Send(&rank, 1, MPI_INT, 0, 0, intercomm);
	MPI_Finalize();
	return 0;
}