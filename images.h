#ifndef IMAGES_H
#define IMAGES_H

#include "SDL.h"

#define COLOR_DEPTH 32

#define ONE_PLAYER_BACKGROUND 0
#define TWO_PLAYER_BACKGROUND 1
#define RED_BLOCK 2
#define GREEN_BLOCK 3
#define BLUE_BLOCK 4
#define YELLOW_BLOCK 5
#define ORANGE_BLOCK 6
#define PURPLE_BLOCK 7
#define DARK_GREEN_BLOCK 8
#define GRAY_BLOCK 9
#define MENU_BACKGROUND 10

#define NUMBER_OF_IMAGES 11

#define DIMENSIONS_PER_IMAGE 4

#define BREAKING_BLOCK_0 10
#define BREAKING_BLOCK_FRAMES 13

SDL_Surface **images_load(const char *filename);
void images_free(SDL_Surface **images, int number_of_images);

#endif /* IMAGES_H */
