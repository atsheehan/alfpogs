#ifndef DRAW_H
#define DRAW_H

#include <stdbool.h>
#include "menu.h"
#include "grid.h"
#include "SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BIT_DEPTH 32

/* This surface represents the user's display. */
SDL_Surface *screen;

bool draw_init(void);
void draw_cleanup(void);

void draw_menu(struct menu *menu);
void draw_game(struct grid *grid);

#endif /* DRAW_H */
