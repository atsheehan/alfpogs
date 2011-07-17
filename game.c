#include "game.h"
#include "draw.h"
#include "input.h"
#include "SDL.h"
#include "SDL_thread.h"

void game_loop(SDL_cond *sync_condition, struct instance *instance) {

  struct display_data display_data;
  SDL_mutex *mutex;

  draw_init(&display_data);

  mutex = SDL_CreateMutex();
  SDL_mutexP(mutex);

  while (!instance->quit) {
    input_game(instance);
    draw_game(instance, &display_data);
    instance_update(instance);

    SDL_CondWait(sync_condition, mutex);
  }

  draw_cleanup(&display_data);

  SDL_DestroyMutex(mutex);
}
