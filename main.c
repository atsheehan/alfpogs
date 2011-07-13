#include <stdio.h>
#include "game.h"
#include "instance.h"
#include "net.h"
#include "SDL.h"
#include "SDL_net.h"
#include "SDL_ttf.h"

Uint32 sync_framerate_func(Uint32 interval, void *_condition);

int main() {

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

  struct grid grids[2];
  grid_init(&grids[0], 1, true);
  grid_init(&grids[1], 1, true);

  int starting_levels[1];
  starting_levels[0] = 1;
  starting_levels[1] = 1;

  struct instance new_instance;
  new_instance.type = MULTI_PLAYER;
  new_instance.num_players = 2;
  new_instance.player_index = 0;
  new_instance.grids = grids;
  new_instance.starting_levels = starting_levels;
  new_instance.quit = false;

  struct net_info net_info;
  if (!net_init(&net_info, "localhost", 4485)) {
    exit(1);
  }
  new_instance.net_info = &net_info;

  // setup timer
  Uint32 interval = 1000 / 30;

  SDL_cond *sync_condition = SDL_CreateCond();
  SDL_TimerID timer_id = SDL_AddTimer(interval, sync_framerate_func, sync_condition);

  game_loop(sync_condition, &new_instance);

  net_destroy(&net_info);

  SDL_RemoveTimer(timer_id);
  SDL_DestroyCond(sync_condition);

  TTF_Quit();
  SDLNet_Quit();
  SDL_Quit();

  return 0;
}


Uint32 sync_framerate_func(Uint32 interval, void *_condition) {
  SDL_cond *condition = (SDL_cond *)_condition;
  SDL_CondBroadcast(condition);

  return interval;
}
