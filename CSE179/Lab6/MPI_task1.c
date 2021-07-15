#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int numprocs, rank, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	//Task 1.1
	int msg = 0;
	if(rank == 0){
		msg = msg + 10;
	}

	MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Process %d: msg = %d\n", rank, msg);
	

	//Task 1.2
	int* arr;
	int u;
	if(rank == 0){
		arr = malloc(numprocs * sizeof(int));
		for(int i = 0; i < numprocs; i++){
			arr[i] = 0;
		}
	}

	MPI_Scatter(arr, 1, MPI_INT, &u, 1, MPI_INT, 0, MPI_COMM_WORLD);
    u += rank;


	MPI_Gather(&u, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0){
		for(int i = 0; i < numprocs; i++){
			printf("arr[%d] = %d\n", i, arr[i]);
		}
	}
	MPI_Finalize();
}