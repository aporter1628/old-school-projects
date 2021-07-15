#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

#define THREADS 4

//Matrix mult; predefine x and A, then multiply
//use gettimeofday from sys/time.h
//set size [512, 512]
//Make a table: how many threads, how large of matrix, execution time for parallel vs serial
//check schedule(static) and schedule(dynamic) and test the time for that
//#pragma omp parallel for schedule(dynamic) num_threads(THREADS)
//#pragma omp parallel for schedule(static) num_threads(THREADS)
//#pragma omp parallel


void multiply(double *A, double *x, double *b, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			double sum = 0;
			for(int k = 0; k < n; k++) {
				sum += A[i*n+k] * x[k*n+j];
			}
			b[i*n+j] = sum;
		}
	}
}

void multiply_omp(double *A, double *x, double *b, int n) {
	#pragma omp parallel for schedule(static) num_threads(THREADS) {
		#pragma omp for
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				double sum = 0;
				for(int k = 0; k < n; k++) {
					sum += A[i*n+k] * x[k*n+j];
				}
				b[i*n+j] = sum;
			}	
		}
	} 
	



int main() {
	int n = 512;

	double *A, *x, *b;
	A = (double*) malloc(sizeof(double)*n*n);
	x = (double*) malloc(sizeof(double)*n*n);
	b = (double*) malloc(sizeof(double)*n*n);

	//Fill the matrices with numbers
	for(int i = 0; i < n*n; i++) {
		A[i] = i;
		x[i] = i;
	}

	struct timeval before;
	struct timeval after;
    gettimeofday(&before, NULL);
    //printf("Before matrix multiplication(serial) / seconds: %d microseconds: %d\n", tv.tv_sec, tv.tv_usec);
	multiply(A, x, b, n);
	gettimeofday(&after, NULL);
	//printf("After mult / seconds: %d microseconds: %d\n", tv.tv_sec, tv.tv_usec);
	printf("Serial code takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

    gettimeofday(&before, NULL);
    //printf("Before matrix multiplication(parallel) / seconds: %d microseconds: %d\n", tv.tv_sec, tv.tv_usec);
	multiply_omp(A, x, b, n);
	gettimeofday(&after, NULL);
	//printf("After mult / seconds: %d microseconds: %d\n", tv.tv_sec, tv.tv_usec);
	printf("Parallel code takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

	return 0;
}