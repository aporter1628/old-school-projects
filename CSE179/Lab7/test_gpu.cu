#include <stdio.h>
#include <cuda.h>
#include <sys/time.h>
#define N 2048


__global__ void findMax(int *a, int *b){
        b[0] = 0;
        if(a[threadIdx.x] > b[0]){
                b[0] = a[threadIdx.x];
        }
        __syncthreads();
}

int findMaxCPU(int *a){
        int max = 0;
        for(int i = 0; i < N; i++){
                if(a[i] > max) {
                        max = a[i];
                }
        }
        return max;
}

int main(int argc, char *argv[]){
        int *a, *b;
        int *d_a, *d_b;
        int size = N * sizeof(int);

         struct timeval before;
        struct timeval after;

        cudaMalloc((void **)&d_a, size);
        cudaMalloc((void**)&d_b, size);
        a = (int *)malloc(size);
        b = (int*)malloc(size);
        //random_ints(a, N);
        for(int i = 0; i < N; i++){
                a[i] = rand();
        }

        cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);


        gettimeofday(&before, NULL);
        findMax<<<1,1>>>(d_a, d_b);

        gettimeofday(&after, NULL);

        cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);
        printf("For GPU, the max is %d and it takes %d microseconds\n", b[0], (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));
        gettimeofday(&before, NULL);
        int max = findMaxCPU(a);
        gettimeofday(&after, NULL);

        printf("For CPU, the max is %d and it takes %d microseconds\n", max, (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));
        free(a); free(b);
        cudaFree(d_a);
        cudaFree(d_b);

        return 0;
}