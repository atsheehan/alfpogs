#include "instance.h"
#include "net.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_net.h"

void instance_update(struct instance *instance) {
  int i;

  if (instance->type == SINGLE_PLAYER) {

    for (i = 0; i < instance->num_players; i++) {
      grid_update(&instance->grids[i]);
    }

  } else {

    struct net_info *net = instance->net_info;

    // check for incoming messages and handle them
    while (SDLNet_UDP_Recv(net->socket, net->packet) > 0) {
      if (net->packet->len < 1) {
	printf("received an empty packet\n");
	continue;
      }

      switch (net->packet->data[0]) {

      case JOINED_GAME_ID:
	printf("received a JOINED_GAME packet\n");
	if (net->state == JOIN_SENT) {
	  net->state = WAIT_START;
	}
	break;

      case GAME_FULL_ID:
	printf("received a GAME_FULL packet\n");
	if (net->state == JOIN_SENT) {
	  net->state = JOIN_DENY;
	}
	break;


      case GRID_UPDATE_ID:
	printf("received a GRID_UPDATE_ID packet\n");
	net->state = RUNNING;

	if (!net_parse_grid_update_buffer((char *)net->packet->data, net->packet->len, instance->grids, instance->num_players)) {
	  fprintf(stderr, "unable to parse grid update packet\n");
	}
	break;

      default:
	break;
      }
    }
    
    // check state to determine if need to send packet
    switch (net->state) {
    case INIT:
      net->packet->len = 1;
      net->packet->data[0] = JOIN_GAME_ID;
      SDLNet_UDP_Send(net->socket, -1, net->packet);
      printf("sent a JOIN_GAME_ID packet\n");      
      net->last_time_sent = net->time;
      net->state = JOIN_SENT;
      break;

    case JOIN_SENT:
      if ((net->time - net->last_time_sent) > 300 ||
	  net->last_time_sent == 0) {

	net->packet->len = 1;
	net->packet->data[0] = JOIN_GAME_ID;
	SDLNet_UDP_Send(net->socket, -1, net->packet);
	net->last_time_sent = net->time;
	printf("sent a JOIN_GAME_ID packet\n");      
      }
      break;

    case JOIN_DENY:
      instance->quit = true;
      break;

    default:
      break;
    }

    instance->net_info->time++;
  }
}
