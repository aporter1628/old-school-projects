#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	int numprocs, rank, namelen;
	int tag = 1;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	struct timeval before;
	struct timeval after;
    gettimeofday(&before, NULL);

	int msg;
	if(rank == 0){
		msg = 0;
		MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process %d is sending msg %d to process %d\n", rank, msg, rank+1);
	}

	while(1){
		MPI_Recv(&msg, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(msg == rank-1){
			printf("Process %d received msg %d from process %d\n", rank, msg, rank-1);
		}

		if(rank != numprocs-1 && msg == rank-1){
			msg = rank;
			MPI_Send(&msg, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
			printf("Process %d is sending msg %d to process %d\n", rank, msg, rank+1);
		}
		break;
	}

	gettimeofday(&after, NULL);
	printf("The whole function takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

	MPI_Finalize();
}