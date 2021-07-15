#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 32

	MPI_Status status;
	int A[N][N], B[N][N], C2[N][N];

int main(int argc, char *argv[]) {
	int numprocs, rank, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	struct timeval before;
	struct timeval after;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	int q;
	/*int *A, *B;
    A = (int*) malloc(N*N*sizeof(int));
    B = (int*) malloc(N*N*sizeof(int));*/
    q = N/(numprocs-1);

	if(rank == 0) {
    	srand(time(NULL));
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++) {
        		A[i][j] = rand() % 10;
            	B[i][j] = rand() % 10;
        	}
    	}

    	//Serial version
    	int *C1;
    	C1 = (int*) malloc(N*N*sizeof(int));
    	//Serial version
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++){
    			C1[i*N+j] = 0;
    			for(int k = 0; k < N; k++){
    				C1[i*N+j] = C1[i*N+j] + A[i][k] * B[k][j];
    			}
    		}
    	}

    	printf("Matrix C:\n");
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++) {
        		printf("%d ", C1[i*N+j]);
        	}
        	printf("\n");
    	}
	}

    //Parallel version
    int offset = 0;

    //Send chunks of A and B to other processes
    if(rank == 0){
    	gettimeofday(&before, NULL);
    	for(int i = 1; i < numprocs; i++){
    		MPI_Send(&offset, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      		MPI_Send(&q, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      		MPI_Send(&A[offset][0], q*N, MPI_INT, i, 1, MPI_COMM_WORLD);
      		MPI_Send(&B, N*N, MPI_INT, i, 1, MPI_COMM_WORLD);
      		offset += q;
      	}

      	//Receive results
 		for(int i = 1; i < numprocs; i++){
 			MPI_Recv(&offset, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
      		MPI_Recv(&q, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
      		MPI_Recv(&C2[offset][0], q*N, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
 		}
 		gettimeofday(&after, NULL);
		printf("The whole function takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

 		printf("Parallel result:\n");
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++) {
        		printf("%d ", C2[i][j]);
        	}
        	printf("\n");
    	}
    }

    //Compute C2
    if(rank > 0){
    	MPI_Recv(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    	MPI_Recv(&q, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    	MPI_Recv(&A, q*N, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    	MPI_Recv(&B, N*N, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

    	//printf("%d ", N);
 		for(int i = 0; i < N; i++){
 			for(int j = 0; j < q; j++){
 				C2[j][i] = 0;
 				for(int k = 0; k < N; k++){
 					C2[j][i] = C2[j][i] + A[j][k] * B[k][i];
 				}
 			}
 		}
 		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    	MPI_Send(&q, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    	MPI_Send(&C2, q*N, MPI_INT, 0, 2, MPI_COMM_WORLD);
 	}


 	  MPI_Finalize();
}