#ifndef GAME_H
#define GAME_H

#include "instance.h"
#include "SDL.h"

void game_loop(SDL_cond *sync_condition, struct instance *instance);

#endif /* GAME_H */
