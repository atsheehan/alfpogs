#include <stdio.h>
#include "game.h"
#include "instance.h"
#include "net.h"
#include "menu.h"
#include "SDL.h"
#include "SDL_net.h"
#include "SDL_ttf.h"

Uint32 sync_framerate_func(Uint32 interval, void *_condition);

int main(int argc, char **argv) {

  struct grid grids[2];
  int starting_levels[1];
  struct instance new_instance;
  struct net_info net_info;
  Uint32 interval;
  SDL_cond *sync_condition;
  SDL_TimerID timer_id;


  // init SDL and all that jazz
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    exit(1);
  }

  if (SDLNet_Init() == -1) {
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    exit(1);
  }

  if (TTF_Init() == -1) {
    fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
    exit(1);
  }


  if (!menu_init(&new_instance.menu)) {
    fprintf(stderr, "menu_init: unable to init menu\n");
    exit(1);
  }


  grid_init(&grids[0], 1, 1);
  grid_init(&grids[1], 1, 1);


  starting_levels[0] = 1;
  starting_levels[1] = 1;

  new_instance.message[0] = 0;
  new_instance.state = STATE_MENU;
  new_instance.game_type = MULTI_PLAYER;
  new_instance.num_players = 2;
  new_instance.player_index = 0;
  new_instance.grids = grids;
  new_instance.starting_levels = starting_levels;

  if (!net_init(&net_info, "69.55.9.123", 4485)) {
    exit(1);
  }
  new_instance.net_info = &net_info;

  // setup timer
  interval = 1000 / 30;

  sync_condition = SDL_CreateCond();
  timer_id = SDL_AddTimer(interval, sync_framerate_func, sync_condition);

  game_loop(sync_condition, &new_instance);

  menu_destroy(&new_instance.menu);

  net_destroy(&net_info);

  SDL_RemoveTimer(timer_id);
  SDL_DestroyCond(sync_condition);

  TTF_Quit();
  SDLNet_Quit();
  SDL_Quit();

  return 0;
}


Uint32 sync_framerate_func(Uint32 interval, void *_condition) {
  SDL_cond *condition;

  condition = (SDL_cond *)_condition;
  SDL_CondBroadcast(condition);

  return interval;
}
