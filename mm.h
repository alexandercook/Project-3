/*
* CSci4061 F2013 Assignment 3
* section: 3
* date: 11/11/13
* name: Devon Grandahl, Alex Cook
* id: 4260296, 4123940 
*/

#ifndef __MM_H
#define __MM_H

#include <sys/time.h>

#define INTERVAL 10000
#define INTERVAL_USEC 100000
#define CHUNK_SIZE 64
#define NUM_CHUNKS 1000

/* TODO - Fill this in */
typedef struct {
	int num_chunks;
	int chunk_size;
	int lowest_open;
	int lowest_closed;
	int* valid;
	void* dyn_mem;
} mm_t;

/* TODO - Implement these in mm_public.c */
double comp_time(struct timeval time_s, struct timeval time_e);
int mm_init(mm_t *mm, int num_chunks, int chunk_size);
void *mm_get(mm_t *mm);
void mm_put(mm_t *mm, void *chunk);
void mm_release(mm_t *mm);

#endif
