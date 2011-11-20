#include <stdio.h>
#include "game.h"
#include "instance.h"
#include "net.h"
#include "input.h"
#include "menu.h"
#include "SDL.h"
#include "SDL_net.h"
#include "SDL_ttf.h"

Uint32 sync_framerate_func(Uint32 interval, void *_condition);

int main(int argc, char **argv) {

  struct instance new_instance;
  Uint32 interval;
  SDL_cond *sync_condition;
  SDL_TimerID timer_id;

  // init SDL and all that jazz
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) == -1) {
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

  if (!instance_init(&new_instance)) {
    fprintf(stderr, "Error initializing the instance.\n");
    exit(1);
  }

  if (!input_init(&new_instance)) {
    fprintf(stderr, "Error initializing the input handling.\n");
    exit(1);
  }

  // setup timer
  interval = 1000 / 30;

  sync_condition = SDL_CreateCond();
  timer_id = SDL_AddTimer(interval, sync_framerate_func, sync_condition);

  game_loop(sync_condition, &new_instance);

  SDL_RemoveTimer(timer_id);
  SDL_DestroyCond(sync_condition);

  input_cleanup(&new_instance);

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
