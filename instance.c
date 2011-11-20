#include "instance.h"
#include "net.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_net.h"

char instance_init(struct instance *instance) {

  instance->state = STATE_MENU;
  instance->game_type = SINGLE_PLAYER;

  if (!menu_init(&instance->menu, instance)) {
    fprintf(stderr, "instance_init: error initializing the menu\n");
    return 0;
  }

  instance->num_players = 1;
  instance->player_index = 0;
  instance->starting_level = 1;

  memset(instance->message, 0, MESSAGE_BUFFER_SIZE);
  memset(instance->host, 0, HOST_NAME_SIZE);
  sprintf(instance->host, "69.55.9.123");

  instance->port = DEFAULT_PORT;
  instance->quit = 0;

  // initialize this stuff later when we know the game type
  instance->net_info = 0;
  instance->grids = 0;

  // this will be initialized with the input
  instance->num_controllers = 0;

  return 1;
}

char instance_single_player_init(struct instance *instance) {
  int i;

  instance->num_players = 1;

  instance->grids = malloc(sizeof(struct grid) * instance->num_players);
  if (instance->grids == NULL) {
    return 0;
  }

  for (i = 0; i < instance->num_players; i++) {
    grid_init(&instance->grids[i], instance->starting_level, 0);
  }

  instance->game_type = SINGLE_PLAYER;
  return 1;
}

char instance_multi_player_init(struct instance *instance) {
  int i;

  instance->num_players = 2;

  instance->grids = malloc(sizeof(struct grid) * instance->num_players);
  if (instance->grids == NULL) {
    return 0;
  }

  for (i = 0; i < instance->num_players; i++) {
    grid_init(&instance->grids[i], instance->starting_level, 1);
  }

  instance->net_info = malloc(sizeof(struct net_info));
  if (instance->net_info == NULL) {
    return 0;
  }

  if (!net_init(instance->net_info, instance->host, instance->port)) {
    return 0;
  }

  instance->game_type = MULTI_PLAYER;
  return 1;
}

void instance_update(struct instance *instance) {
  int i;

  switch (instance->state) {

  case STATE_MENU:
    break;

  case STATE_RUNNING:
    if (instance->game_type == SINGLE_PLAYER) {

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

	case MESSAGE_ID:
	  strncpy(instance->message, (char *)&net->packet->data[1], MESSAGE_BUFFER_SIZE - 1);
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
	instance->state = STATE_QUITTING;
	break;

      default:
	break;
      }

      instance->net_info->time++;
    }
    break;

  default:
    break;
  }
}

void instance_destroy(struct instance *instance) {
}
