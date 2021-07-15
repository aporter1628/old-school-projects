#include <omp.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define THREADS 4

#define SEED       2531
#define RAND_MULT  1366
#define RAND_ADD   150889
#define RAND_MOD   714025
int randy = SEED;

void fill_rand(int length, double *a)
{
   int i; 
   #pragma omp parallel for num_threads(4)
   for (i=0;i<length;i++) {
     randy = (RAND_MULT * randy + RAND_ADD) % RAND_MOD;
     *(a+i) = ((double) randy)/((double) RAND_MOD);
   }   
}

void sum(double *x, double *y, int size){
	struct timeval before;
	struct timeval after;
    gettimeofday(&before, NULL);
	*y = *x;
	#pragma omp parallel for schedule(static)
	for(int i = 0; i < size; i++){
		if(i != 0)
			*(y+i) = *(y+(i-1)) + *(x+i);
		//printf("%f, ", *(y+i));
	}
	gettimeofday(&after, NULL);
	printf("Step1 takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

    gettimeofday(&before, NULL);
	//Make array T with T[i] = y[(length/threads*(i-1))
	double *t = (double *)malloc((size/4)*sizeof(double));
	*t = 0;
	for(int i = 1; i < size/4; i++){
		*(t+i) = *(y + ((size/4)*(i))-1) + *(t+(i-1));
		//printf("%f, ", *(t+i));
	}
	gettimeofday(&after, NULL);
	printf("Step2 takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

    gettimeofday(&before, NULL);
	//Add t[threadid] to every portion of y
	#pragma omp parallel for schedule(static)
	for(int i = 0; i < size; i++){
		//printf("%f, ", omp_get_thread_num());
		*(y+i) = *(y+i) + *(t + omp_get_thread_num());
	}
	gettimeofday(&after, NULL);
	printf("Step3 takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

	//printf("%f ", size);
	for(int i = 0; i < size; i++){
		//printf("%f, ", *(y+i));
	}
	printf("\n");
}

int main() {
	int size = 512;
	double *y; double *x;

	y = (double *)malloc(size*sizeof(double));
	x = (double *)malloc(size*sizeof(double));

	fill_rand(size, x);

	for(int i = 0; i < size; i++){
		*(x+i) = 1;
		//printf("%f ", *(x+i));
	}

	//printf("test\n");
	struct timeval before;
	struct timeval after;
    gettimeofday(&before, NULL);
    //printf("test\n");
	sum(x, y, size);
	//printf("test\n");
	gettimeofday(&after, NULL);
	printf("The whole function takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

}




