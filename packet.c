#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "mm.h"

#define MAX_PACKETS 10

typedef char data_t[56];

typedef struct {
  int how_many; /* number of packets in the message */
  int which;    /* which packet in the message -- currently ignored */
  data_t data;  /* packet data */
} packet_t;

/* Keeps track of packets that have arrived for the message */
typedef struct {
  int num_packets;
  void *data[MAX_PACKETS];
} message_t;

static message_t message;   /* current message structure */
static mm_t mm;             /* memory manager will allocate memory for packets */
static int pkt_cnt = 0;     /* how many packets have arrived for current message */
static int pkt_total = 3;   /* how many packets to be received for the message */
static int NUM_MESSAGES = 3; /* number of messages we will receive */

static packet_t get_packet() {
  static int which = 0;

  packet_t pkt;

  pkt.how_many = 3;
  pkt.which = which;

  switch (which) {
    case 0:
      strcpy(pkt.data, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
      break;
    case 1:
      strcpy(pkt.data, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
      break;
    default:
      strcpy(pkt.data, "cccccccccccccccccccccccccccccccccccccccccccccccccccccccc\0");
  }

  which = (which + 1) % 3;

  return pkt;
}

/* TODO - implement */
static void packet_handler(int sig) {
  packet_t pkt;
  fprintf (stderr, "IN PACKET HANDLER, sig=%d\n", sig);  /* TODO - debug only */
  pkt = get_packet();
  /* TODO - insert your code here ... stick packet in memory */
    char* pkt_pointer;
    pkt_pointer = mm_get(&mm);
	*pkt_pointer= "e";
	pkt_cnt+=1;
	mm_put(&mm, (void*) pkt_pointer);
}

/*
 * TODO - Create message from packets ... deallocate packets.
 * Return a pointer to the message on success, or NULL and set errno on
 * failure.
 */
static char *assemble_message() {

  char * msg;
	char * memory;
	int i;

  /* TODO - Allocate msg and assemble packets into it */
	msg = (char*) malloc (CHUNK_SIZE * NUM_CHUNKS);
	for(i=0; i<=pkt_total; i++){
		*memory = mm_get(&mm);
		memcpy (msg+(i * CHUNK_SIZE), memory, CHUNK_SIZE);
	}
	

  /* reset these for next message */
  pkt_total = 1;
  pkt_cnt = 0;
  message.num_packets = 0;

  return msg;
}

int main(int argc, char **argv) {
  int i;
  char *msg;

  /* TODO - init memory manager for NUM_CHUNKS chunks of size CHUNK_SIZE each */
    mm_init(&mm, NUM_CHUNKS, CHUNK_SIZE);
  /* TODO - set up alarm handler -- mask all signals within it */
    struct sigaction act;

    act.sa_handler = packet_handler;
    act.sa_flags = 0;

    if((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGALRM,&act,NULL)) == -1)
    {
        perror("Failed to set SIGALARM handler!\n");
        return -1;
    }
  /*
   * TODO - turn on alarm timer ...
   * use  INTERVAL and INTERVAL_USEC for sec and usec values
   */
  message.num_packets = 0;
    struct timeval time_s, time_e;

  fprintf(stderr, "Time taken = %f msec\n",
          comp_time(time_s, time_e) / 1000.0);

	alarm(1);
	sleep(1);
	alarm(1);
	sleep(1);
	alarm(1);

  for (i = 1; i <= NUM_MESSAGES; i++) {
    while (pkt_cnt < pkt_total) {
      pause(); /* block until next packet */
    }

    msg = assemble_message();
    if (msg == NULL) {
      perror("Failed to assemble message");
    }
    else {
      fprintf(stderr, "GOT IT: message=%s\n", msg);
      free(msg);
    }
  }

  /* TODO - Deallocate memory manager */
    mm_release(&mm);

  return EXIT_SUCCESS;
}
