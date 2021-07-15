#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	int numprocs, rank, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	//Task 2.1
	MPI_Comm comm;
	int size = 16; //size of the topology
	int dim[2] = {4, 4}; //topology dimension
	int period[2] = {0, 0};
	int coord[2];

	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 0, &comm);

	int newRank;
	//Get coordinates of the processor
	MPI_Cart_coords(comm, rank, 2, coord);
	//Get the global rank of the processor
	MPI_Cart_rank(comm, coord, &newRank);
	//Print out local rank and global rank
	printf("Local rank: %d, global rank: %d\n", rank, newRank);

	//Calculate the average between this rank and the one's in north, south, east, and west
	int rank1;
	int th = rank;
	double average;
	
	//Shift up
	MPI_Cart_shift(comm, 0, 1, &rank, &rank1);
	average = (double) (rank1 + rank)/2;
	printf("Average between %d and up: %lf\n", th, average);
	//Shift down
	MPI_Cart_shift(comm, 0, -1, &rank, &rank1);
	average = (double) (rank1 + rank)/2;
	printf("Average between %d and down: %lf\n", th, average);

	//Shift left
	MPI_Cart_shift(comm, 1, -1, &rank, &rank1);
	average = (double) (rank1 + rank)/2;
	printf("Average between %d and left: %lf\n", th, average);
	//Shift right
	MPI_Cart_shift(comm, 1, 1, &rank, &rank1);
	average = (double) (rank1 + rank)/2;
	printf("Average between %d and right: %lf\n", th, average);

	/*int destRank;
	for(int i = 0; i < 2; i++){
		for(int j = -1; j < 2; j+=2){
			MPI_Cart_shift(comm, i, j, &rank, &destRank);
			printf("Average between %d and %d: %d\n", newRank, destRank, (rank + destRank)/2);
		}
	}*/
	MPI_Finalize();
}