/*
* CSci4061 F2013 Assignment 3
* section: 3
* date: 11/11/13
* name: Devon Grandahl, Alex Cook
* id: 4260296, 4123940 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"


int main(int argc, char **argv){
	void* objects[NUM_CHUNKS];
	int i; 
	struct timeval time_s, time_e;

	  /* start timer */
	gettimeofday (&time_s, NULL);
	//1 million "gets"
	for (i=0; i < NUM_CHUNKS; i++){
		objects[i] = malloc(CHUNK_SIZE);
	}
	//1 million "puts"
	for (i=0; i < NUM_CHUNKS; i++){
		free(objects[i]);
	}
	gettimeofday(&time_e, NULL);

	fprintf(stderr, "Time taken = %f msec\n",
	    comp_time(time_s, time_e) / 1000.0);
	return 0;
}
