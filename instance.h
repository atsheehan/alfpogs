#ifndef INSTANCE_H
#define INSTANCE_H

#include "grid.h"
#include "menu.h"
#include "net.h"
#include "SDL.h"

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

  char host[HOST_NAME_SIZE];
  int port;

  char quit;

  struct net_info *net_info;
  struct grid *grids;
  int starting_level;

  int num_controllers;
  SDL_Joystick *controllers[MAX_NUM_PLAYERS];
  
};

char instance_init(struct instance *instance);
void instance_destroy(struct instance *instance);
void instance_update(struct instance *instance);
char instance_single_player_init(struct instance *instance);
char instance_multi_player_init(struct instance *instance);

#endif /* INSTANCE_H */
