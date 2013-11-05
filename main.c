//main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"

int main(int argc, char **argv){
	mm_t myMem;
	mm_init(&myMem, 100, 12); //100 12 byte chunks
	int i; 
	
	for (i = 0; i < 100; i++){
		printf("Chunk %d has a valid bit of %d.\n", i , (myMem . valid[i]));
	}
	
	//test mm_get
	char* wordTest; 
	mm_get(&myMem);
	mm_get(&myMem);
	mm_get(&myMem);
	mm_get(&myMem);
	mm_get(&myMem);
	mm_get(&myMem);
	mm_get(&myMem);
	wordTest = mm_get(&myMem);
	*wordTest = 'h';
	*(wordTest + 1) = 'e';
	*(wordTest + 2) = 'l';
	*(wordTest + 3) = 'l';
	*(wordTest + 4) = 'o';
	*(wordTest + 5) = 0;
	for (i = 0; i < 10; i++){
		printf("Chunk %d has a valid bit of %d.\n", i , (myMem . valid[i]));
	}
	printf("%s\n", wordTest);

	//test mm_put
	mm_put(&myMem,(void*) wordTest);
	for (i = 0; i < 10; i++){
		printf("Chunk %d has a valid bit of %d.\n", i , (myMem . valid[i]));
	}
	printf("%s\n", wordTest); //expect still there

	for (i = 0; i < 100; i++){
		printf("Chunk %d has a valid bit of %d.\n", i , (myMem . valid[i]));
	}
	//test mm_release
	mm_release(&myMem);
	printf("%d\n", (myMem . valid)[5]); //expect seg fault
	return 0;
}