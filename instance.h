#ifndef INSTANCE_H
#define INSTANCE_H

#include "grid.h"
#include "menu.h"
#include "net.h"

#define MAX_NUM_PLAYERS 2
#define MESSAGE_BUFFER_SIZE 1000

enum game_type {
  SINGLE_PLAYER,
  MULTI_PLAYER
};

enum game_state {
  STATE_MENU,
  STATE_RUNNING,
  STATE_QUITTING
};

struct instance {
  enum game_state state;
  enum game_type game_type;

  struct menu menu;

  int num_players;
  int player_index;
  char message[MESSAGE_BUFFER_SIZE];

  char *host;
  int port;

  char quit;

  struct net_info *net_info;
  struct grid *grids;
  int *starting_levels;
};

void instance_update(struct instance *instance);

#endif /* INSTANCE_H */
