#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "net.h"

struct net_grid_header {
  uint32_t lines_cleared;
  uint32_t score;
  uint8_t next_shape_index;
  uint8_t level;
};

bool net_init(struct net_info *net_info, const char *hostname, int port) {
  
  net_info->socket = SDLNet_UDP_Open(0);
  if (net_info->socket == NULL) {
    fprintf(stderr, "unable to create a UDP socket: %s\n", SDLNet_GetError());
    return false;
  }

  net_info->packet = SDLNet_AllocPacket(PACKET_BUFFER_SIZE);
  if (net_info->packet == NULL) {

    fprintf(stderr, "unable to allocate a new UDP packet: %s\n", SDLNet_GetError());
    SDLNet_UDP_Close(net_info->socket);
    return false;
  }

  if (SDLNet_ResolveHost(&net_info->packet->address, hostname, port) == -1) {

    fprintf(stderr, "unable to resolve host: %s\n", SDLNet_GetError());
    SDLNet_FreePacket(net_info->packet);
    SDLNet_UDP_Close(net_info->socket);
    return false;
  }

  net_info->state = INIT;
  net_info->last_time_sent = 0;
  net_info->last_time_received = 0;
  net_info->time = 1;


  return true;
}

void net_destroy(struct net_info *net_info) {
    SDLNet_FreePacket(net_info->packet);
    SDLNet_UDP_Close(net_info->socket);
}

bool net_prepare_grid_update_buffer(char *buffer, int *buffer_size, struct grid *grids, int num_players) {
  
  /* if (*buffer_size < GRID_SIZE * num_players + 1) { */
  /*   return false; */
  /* } */

  struct net_grid_header header;

  int buffer_index = 0;
  buffer[buffer_index++] = GRID_UPDATE_ID;

  int i, row, col;
  for (i = 0; i < num_players; i++) {

    header.lines_cleared = htonl(grids[i].lines_cleared);
    header.score = htonl(grids[i].score);
    header.next_shape_index = grids[i].next_shape_index;
    header.level = grids[i].level;

    memcpy(&buffer[buffer_index], &header, sizeof(struct net_grid_header));
    buffer_index += sizeof(struct net_grid_header);

    for (row = 0; row < GRID_ROWS; row++) {
      for (col = 0; col < GRID_COLUMNS; col++, buffer_index++) {
  	buffer[buffer_index] = grid_get_block_value(&grids[i], row, col);
      }
    }
  }

  *buffer_size = buffer_index + 1;

  return true;
}

bool net_parse_grid_update_buffer(char *buffer, int buffer_size, struct grid *grids, int num_players) {

  /* if (buffer_size < GRID_SIZE * num_players + 1) { */
  /*   return false; */
  /* } */

  int buffer_index = 0;
  struct net_grid_header header;

  if (buffer[buffer_index++] != GRID_UPDATE_ID) {
    return false;
  }

  int i;
  for (i = 0; i < num_players; i++) {

    memcpy(&header, &buffer[buffer_index], sizeof(struct net_grid_header));

    grids[i].lines_cleared = ntohl(header.lines_cleared);
    grids[i].score = ntohl(header.score);
    grids[i].next_shape_index = header.next_shape_index;
    grids[i].level = header.level;

    buffer_index += sizeof(struct net_grid_header);

    memcpy(&grids[i].blocks, &buffer[buffer_index], GRID_SIZE);
    buffer_index += GRID_SIZE;
  }

  return true;
}
