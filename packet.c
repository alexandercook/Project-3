#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
static int pkt_total = 1;   /* how many packets to be received for the message */
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
      strcpy(pkt.data, "cccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
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
}

/*
 * TODO - Create message from packets ... deallocate packets.
 * Return a pointer to the message on success, or NULL and set errno on
 * failure.
 */
static char *assemble_message() {

  char *msg;

  /* TODO - Allocate msg and assemble packets into it */

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

  /* TODO - set up alarm handler -- mask all signals within it */

  /*
   * TODO - turn on alarm timer ...
   * use  INTERVAL and INTERVAL_USEC for sec and usec values
   */

  message.num_packets = 0;

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

  return EXIT_SUCCESS;
}
