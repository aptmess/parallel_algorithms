#include <stdio.h>
#include <iostream>
#include "mpi.h"
#define BUFSIZE 100

using namespace std;


int main(int argc, char **argv)
{
	int bufsize, num, sum;
	
	MPI_Init(&argc, &argv);
	
	MPI_Status status;
	MPI_File fh;

	char buf[BUFSIZE];
	const char* filename = "file.txt";
	string message ("hello my dear friend!");

	int len = message.length();
	const char *cstr = message.c_str();
	
	// start of writing to file "file.txt" with text "Hello world!"
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_write(fh, cstr, len, MPI_CHAR, &status);
	MPI_File_close(&fh);
	// end of writing to file

	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//print the number of read symbols sum from the file
	printf("number of read symbols %d\n", sum);
	if ((argc > 1) && (string(argv[1]) == "--delete-file"))
	{
		MPI_File_delete(filename, MPI_INFO_NULL);
	}
	MPI_Finalize();
}