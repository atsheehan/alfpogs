#include <unistd.h>
#include "timer.h"
#include "SDL.h"

static SDL_TimerID timer_id;
static SDL_cond *sync_condition;

static Uint32 timer_sync_func(Uint32 interval, void *unused);

bool timer_init(void) {
  sync_condition = SDL_CreateCond();
  if (sync_condition == NULL) {
    return false;
  }

  Uint32 interval = 1000 / FRAMES_PER_SECOND;
  timer_id = SDL_AddTimer(interval, timer_sync_func, NULL);
  if (timer_id == NULL) {
    SDL_DestroyCond(sync_condition);
    return false;
  }

  return true;
}


void timer_cleanup(void) {
  SDL_RemoveTimer(timer_id);
  SDL_DestroyCond(sync_condition);
}

void timer_wait_for_next_frame(SDL_mutex *mutex) {
  SDL_CondWait(sync_condition, mutex);
  //sleep(1);
}


static Uint32 timer_sync_func(Uint32 interval, void *unused) {
  SDL_CondBroadcast(sync_condition);
  return interval;
}

