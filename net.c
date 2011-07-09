#include <stdio.h>
#include "net.h"

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
