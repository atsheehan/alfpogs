#ifndef DRAW_H
#define DRAW_H

#include "SDL.h"
#include "instance.h"
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct display_data {
  SDL_Surface *screen;
  SDL_Surface **images;
  Uint32 black;
};

bool draw_init(struct display_data *data);
void draw_cleanup(struct display_data *data);

void draw_game(struct instance *instance, struct display_data *display_data);

#endif /* DRAW_H */
