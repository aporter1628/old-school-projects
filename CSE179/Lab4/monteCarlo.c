#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define NUM_THREADS 32


void *compute_pi (void* s) {
	int seed, i, *hit_pointer;
	double x_coord, y_coord;
	int local_hits;
	int sample_points_per_thread = 10000;
	
	hit_pointer = (int*) s;
	seed = *hit_pointer;
	local_hits = 0;

	for(i = 0; i < sample_points_per_thread; i++){
		x_coord = (double) (rand_r(&seed))/(RAND_MAX) - 0.5;
		y_coord = (double) (rand_r(&seed))/(RAND_MAX) - 0.5;
		if((x_coord * x_coord + y_coord * y_coord) < 0.25)
			local_hits++;
	}

	*hit_pointer = local_hits;
	pthread_exit(0);
}

int main(){
	int i;
	int hits[NUM_THREADS];
	int total_hits;
	double pi;
	int sample_points_per_thread = 10000;

	pthread_t p_threads[NUM_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct timeval before;
	struct timeval after;
    gettimeofday(&before, NULL);

	for(i = 0; i < NUM_THREADS; i++){
		hits[i] = i;
		pthread_create(&p_threads[i], &attr, compute_pi, (void*) &hits[i]);
	}

	for(i = 0; i < NUM_THREADS; i++){
		pthread_join(p_threads[i], NULL);
		total_hits += hits[i];
	}

	pi = (double) 4 * (total_hits)/(NUM_THREADS * sample_points_per_thread);
	printf("pi is about %lf\n", pi);

	gettimeofday(&after, NULL);
	printf("The whole function takes %d microseconds\n", (after.tv_sec * 1000000 + after.tv_usec) - (before.tv_sec * 1000000 + before.tv_usec));

	return 0;
}