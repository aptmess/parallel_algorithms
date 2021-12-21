#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int got, send = 42;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	printf("Attempt to connect \n");
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("Server connection \n");
	
	MPI_Send(&send, 1, MPI_INT, 0, 0, intercomm);
	printf("Client sent value: %d\n", send);

	MPI_Recv(&got, 1, MPI_INT, 0, 0, intercomm, &status);
	printf("Client got value: %d\n", got);

	MPI_Finalize();
	return 0;
}