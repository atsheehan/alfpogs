#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "net.h"

struct net_grid_header {
  uint32_t lines_cleared;
  uint32_t score;
  uint8_t next_shape_index;
  uint8_t level;
};

char net_init(struct net_info *net_info, const char *hostname, int port) {
  
  net_info->socket = SDLNet_UDP_Open(0);
  if (net_info->socket == NULL) {
    fprintf(stderr, "unable to create a UDP socket: %s\n", SDLNet_GetError());
    return 0;
  }

  net_info->packet = SDLNet_AllocPacket(PACKET_BUFFER_SIZE);
  if (net_info->packet == NULL) {

    fprintf(stderr, "unable to allocate a new UDP packet: %s\n", SDLNet_GetError());
    SDLNet_UDP_Close(net_info->socket);
    return 0;
  }

  if (SDLNet_ResolveHost(&net_info->packet->address, hostname, port) == -1) {

    fprintf(stderr, "unable to resolve host: %s\n", SDLNet_GetError());
    SDLNet_FreePacket(net_info->packet);
    SDLNet_UDP_Close(net_info->socket);
    return 0;
  }

  net_info->state = INIT;
  net_info->last_time_sent = 0;
  net_info->last_time_received = 0;
  net_info->time = 1;


  return 1;
}

void net_destroy(struct net_info *net_info) {
    SDLNet_FreePacket(net_info->packet);
    SDLNet_UDP_Close(net_info->socket);
}

char net_prepare_grid_update_buffer(char *buffer, int *buffer_size, struct grid *grids, int num_players) {
  
  /* if (*buffer_size < GRID_SIZE * num_players + 1) { */
  /*   return 0; */
  /* } */

  struct net_grid_header header;
  int buffer_index;
  int i, row, col;

  buffer_index = 0;
  buffer[buffer_index++] = GRID_UPDATE_ID;

  for (i = 0; i < num_players; i++) {

    SDLNet_Write32(grids[i].lines_cleared, &header.lines_cleared);
    SDLNet_Write32(grids[i].score, &header.score);
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

  return 1;
}

char net_parse_grid_update_buffer(char *buffer, int buffer_size, struct grid *grids, int num_players) {

  int i;
  int buffer_index;
  struct net_grid_header header;

  buffer_index = 0;
  if (buffer[buffer_index++] != GRID_UPDATE_ID) {
    return 0;
  }

  for (i = 0; i < num_players; i++) {

    memcpy(&header, &buffer[buffer_index], sizeof(struct net_grid_header));

    grids[i].lines_cleared = SDLNet_Read32(&header.lines_cleared);
    grids[i].score = SDLNet_Read32(&header.score);
    grids[i].next_shape_index = header.next_shape_index;
    grids[i].level = header.level;

    buffer_index += sizeof(struct net_grid_header);

    memcpy(&grids[i].blocks, &buffer[buffer_index], GRID_SIZE);
    buffer_index += GRID_SIZE;
  }

  return 1;
}
