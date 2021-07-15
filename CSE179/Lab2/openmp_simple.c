#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel
	{
	int thread = omp_get_thread_num();
	printf("Hello World, thread #%d\n", thread);

	int numThreads = omp_get_num_threads();
	printf("There are %d threads\n", numThreads);
	}
	return 0;
}