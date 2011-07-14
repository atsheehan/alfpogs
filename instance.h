#ifndef INSTANCE_H
#define INSTANCE_H

#include <stdbool.h>
#include "grid.h"
#include "net.h"

#define MAX_NUM_PLAYERS 2
#define MESSAGE_BUFFER_SIZE 1000

enum instance_type {
  SINGLE_PLAYER,
  MULTI_PLAYER
};

struct instance {
  enum instance_type type;
  int num_players;
  int player_index;
  char message[MESSAGE_BUFFER_SIZE];

  char *host;
  int port;

  bool quit;

  struct net_info *net_info;
  struct grid *grids;
  int *starting_levels;
};

void instance_update(struct instance *instance);

#endif /* INSTANCE_H */
