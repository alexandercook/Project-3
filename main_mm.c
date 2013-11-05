#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"


int main(int argc, char **argv){
	mm_t myMem;
	mm_init(&myMem, NUM_CHUNKS, CHUNK_SIZE); 
	void* objects[NUM_CHUNKS];
	int i; 
	struct timeval time_s, time_e;

	gettimeofday (&time_s, NULL);
	for (i=0; i < NUM_CHUNKS; i++){
		objects[i] = mm_get(&myMem);
	}
	for (i=0; i < NUM_CHUNKS; i++){
		mm_put(&myMem, objects[i]);
	}
	gettimeofday(&time_e, NULL);

	

	fprintf(stderr, "Time taken = %f msec\n",
	    comp_time(time_s, time_e) / 1000.0);

	mm_release(&myMem);
	return 0;
}