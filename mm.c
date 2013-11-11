/*
* CSci4061 F2013 Assignment 3
* section: 3
* date: 11/11/13
* name: Devon Grandahl, Alex Cook
* id: 4260296, 4123940 
*/

#include <stdio.h>
#include <stdlib.h>
#include "mm.h"

/* Return usec */
double comp_time(struct timeval time_s, struct timeval time_e) {

  double elap = 0.0;

  if (time_e.tv_sec > time_s.tv_sec) {
    elap += (time_e.tv_sec - time_s.tv_sec - 1) * 1000000.0;
    elap += time_e.tv_usec + (1000000 - time_s.tv_usec);
  }
  else {
    elap = time_e.tv_usec - time_s.tv_usec;
  }
  return elap;
}

/* TODO - Implement.  Return 0 for success, or -1 and set errno on fail. */
int mm_init(mm_t *mm, int hm, int sz) {
  mm -> num_chunks = hm;
  mm -> chunk_size = sz;
  mm -> lowest_open = 0;
  mm -> lowest_closed = hm;
  mm -> valid = (int*) malloc (hm * sizeof(int)); 
  mm -> dyn_mem = (void*) malloc(hm * sz); //+1 for valid char
  if (mm->dyn_mem == NULL){
    return -1;
  }
  int i;
  for (i = 0; i < hm; i++){
    (mm -> valid)[i] = 0; //sets valid bits to zero
  }
  return 0;  /* TODO - return the right value */
}

/* TODO - Implement */
void *mm_get(mm_t *mm) {
  int open, temp;

  open = mm -> lowest_open;
  if (open >= mm->num_chunks)   
  {
    printf("No available memory.\n");
    return NULL;
  }
  else{
    mm -> valid [open] = 1; //no longer open
    if (open < mm -> lowest_closed ){
      mm -> lowest_closed = open;
     // printf("lowest_closed: %d\n", mm -> lowest_closed );
    }
    temp = open; 
    //find next open position
    while (temp < mm -> num_chunks && mm -> valid[temp] != 0){
      temp++; //find open memory
    }
    mm -> lowest_open = temp;

    //printf("lowest_open: %d\n", mm -> lowest_open);
    return (void*) (mm -> dyn_mem) + open * mm->chunk_size; 
  }
}

/* TODO - Implement */
void mm_put(mm_t *mm, void *chunk) {
  int chunk_num = mm -> lowest_closed;
  void* temp = (mm -> dyn_mem) + (chunk_num * mm -> chunk_size);
  int i = 0;
//printf("The chunk is %d\n", chunk_num);
  while (chunk_num < mm -> num_chunks && temp != chunk){
     //   printf("Didn't find chunk for i: %d, %d\n",i++, chunk_num );
    chunk_num++; //find chunk
    temp += mm -> chunk_size;

  }

  if (chunk_num >= mm -> num_chunks){
    printf("Chunk of memory does not exist. %d, %d\n", mm -> lowest_closed, mm -> lowest_open);
    return;
  }
  else{
    mm->valid [chunk_num] = 0; //set to open
  }
  if (chunk_num < mm -> lowest_open){
    mm -> lowest_open = chunk_num;
  }
  //update lowest_closed
  if (chunk_num == mm -> lowest_closed){
    //printf("lowest closed: %d , %d\n", mm -> lowest_closed, chunk_num);
   while (chunk_num < mm -> num_chunks && mm -> valid[chunk_num] == 0){
      chunk_num++; //find closed memory
    }
    mm -> lowest_closed = chunk_num;
  }
}

/* TODO - Implement */
void mm_release(mm_t *mm) {
  free(mm -> valid);
  mm -> valid = NULL;
  free(mm -> dyn_mem);
  mm -> dyn_mem = NULL;
  mm = NULL;
}

/*
 * TODO - This is just an example of how to use the timer.  Notice that
 * this function is not included in mm_public.h, and it is defined as static,
 * so you cannot call it from other files.  Instead, just follow this model
 * and implement your own timing code where you need it.
 */
static void timer_example() {
  struct timeval time_s, time_e;

  /* start timer */
  gettimeofday (&time_s, NULL);

  /* TODO - code you wish to time goes here */

  gettimeofday(&time_e, NULL);

  fprintf(stderr, "Time taken = %f msec\n",
          comp_time(time_s, time_e) / 1000.0);
}
