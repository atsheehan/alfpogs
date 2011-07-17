#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "grid.h"
#include "shape.h"
#include "instance.h"
#include "images.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define BLOCK_SIZE 20

#define P1_G1_GRID_TOP 40
#define P1_G1_GRID_LEFT 220

#define P1_G2_GRID_TOP 40
#define P1_G2_GRID_LEFT 115

#define P2_G2_GRID_TOP 40
#define P2_G2_GRID_LEFT 325

#define P1_G1_NEXT_TOP 150
#define P1_G1_NEXT_LEFT 490

#define P1_G2_NEXT_TOP 50
#define P1_G2_NEXT_LEFT 15

#define P2_G2_NEXT_TOP 50
#define P2_G2_NEXT_LEFT 545

#define P1_G1_SCORE_TOP 150 // TODO
#define P1_G1_SCORE_LEFT 490 // TODO

#define P1_G2_SCORE_TOP 170
#define P1_G2_SCORE_LEFT 15

#define P2_G2_SCORE_TOP 170
#define P2_G2_SCORE_LEFT 545

#define P1_G1_LEVEL_TOP 150 // TODO
#define P1_G1_LEVEL_LEFT 490 // TODO

#define P1_G2_LEVEL_TOP 240
#define P1_G2_LEVEL_LEFT 15

#define P2_G2_LEVEL_TOP 240
#define P2_G2_LEVEL_LEFT 545

#define P1_G1_LINES_TOP 150 // tODO
#define P1_G1_LINES_LEFT 490 // TODO

#define P1_G2_LINES_TOP 310
#define P1_G2_LINES_LEFT 15

#define P2_G2_LINES_TOP 310
#define P2_G2_LINES_LEFT 545

#define MASTER_IMAGE_FILENAME "images.png"


SDL_Surface *get_block_surface(SDL_Surface **images, unsigned char value, int animation_index);
void draw_grid(struct display_data *display, struct grid *instance, int start_x, int start_y);
void draw_next_shape(struct display_data *display, unsigned char next_shape_index, int start_x, int start_y);
void draw_text(struct display_data *display, const char *text, int start_x, int start_y, SDL_Color color);

char draw_init(struct display_data *data) {

  data->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH, SDL_SWSURFACE);
  if (data->screen == NULL) {
    fprintf(stderr, "SDL_SetVideoMode: %s\n", SDL_GetError());
    return 0;
  }

  data->images = images_load(MASTER_IMAGE_FILENAME);
  if (data->images == NULL) {
    fprintf(stderr, "could not load the images properly\n");
    return 0;
  }

  data->black = SDL_MapRGB(data->screen->format, 0, 0, 0);
  data->white.r = 255;
  data->white.g = 255;
  data->white.b = 255;

  data->font = TTF_OpenFont("font.ttf", 26);
  if (data->font == NULL) {
    fprintf(stderr, "could not load font\n");
    return 0;
  }

  return 1;
}

/* Clean up any resources used by the drawing subsystem. */
void draw_cleanup(struct display_data *data) {
  if (data->font != NULL) {
    TTF_CloseFont(data->font);
  }

  if (data->images != NULL) {
    images_free(data->images, NUMBER_OF_IMAGES);
  }
}


/* Draws any graphics to the screen while playing the game. */
void draw_game(struct instance *instance, struct display_data *display) {

  SDL_Surface *background;

  if (instance->num_players == 1) {
    background = display->images[ONE_PLAYER_BACKGROUND];
  } else {
    background = display->images[TWO_PLAYER_BACKGROUND];
  }

  SDL_FillRect(display->screen, NULL, display->black);
  SDL_BlitSurface(background, NULL, display->screen, NULL);

  if (instance->num_players == 1) {
    draw_grid(display, &instance->grids[0], P1_G1_GRID_LEFT, P1_G1_GRID_TOP);
    draw_next_shape(display, instance->grids[0].next_shape_index, P1_G1_NEXT_LEFT, P1_G1_NEXT_TOP);

    draw_text(display, "score", P1_G1_SCORE_LEFT, P1_G1_SCORE_TOP, display->white);
    draw_text(display, "level", P1_G1_LEVEL_LEFT, P1_G1_LEVEL_TOP, display->white);
    draw_text(display, "lines", P1_G1_LINES_LEFT, P1_G1_LINES_TOP, display->white);

  } else {
    draw_grid(display, &instance->grids[0], P1_G2_GRID_LEFT, P1_G2_GRID_TOP);
    draw_grid(display, &instance->grids[1], P2_G2_GRID_LEFT, P2_G2_GRID_TOP);

    draw_next_shape(display, instance->grids[0].next_shape_index, P1_G2_NEXT_LEFT, P1_G2_NEXT_TOP);
    draw_next_shape(display, instance->grids[1].next_shape_index, P2_G2_NEXT_LEFT, P2_G2_NEXT_TOP);

    sprintf(display->text_buffer, "%.7d", instance->grids[0].score);
    draw_text(display, display->text_buffer, P1_G2_SCORE_LEFT, P1_G2_SCORE_TOP, display->white);
    sprintf(display->text_buffer, "%.7d", instance->grids[1].score);
    draw_text(display, display->text_buffer, P2_G2_SCORE_LEFT, P2_G2_SCORE_TOP, display->white);

    sprintf(display->text_buffer, "%.7d", instance->grids[0].lines_cleared);
    draw_text(display, display->text_buffer, P1_G2_LEVEL_LEFT, P1_G2_LEVEL_TOP, display->white);
    sprintf(display->text_buffer, "%.7d", instance->grids[1].lines_cleared);
    draw_text(display, display->text_buffer, P2_G2_LEVEL_LEFT, P2_G2_LEVEL_TOP, display->white);

    sprintf(display->text_buffer, "%.2d", instance->grids[0].level);
    draw_text(display, display->text_buffer, P1_G2_LINES_LEFT, P1_G2_LINES_TOP, display->white);
    sprintf(display->text_buffer, "%.2d", instance->grids[1].level);
    draw_text(display, display->text_buffer, P2_G2_LINES_LEFT, P2_G2_LINES_TOP, display->white);
  }

  draw_text(display, instance->message, 0, 0, display->white);

  SDL_Flip(display->screen);
}

void draw_next_shape(struct display_data *display, unsigned char next_shape_index, int start_x, int start_y) {

  SDL_Rect block;
  int row, col;
  unsigned char grid_value;
  SDL_Surface *color_block;
  unsigned char *shape_array;

  if (next_shape_index >= SHAPES) {
    return;
  }

  block.w = block.h = BLOCK_SIZE;

  shape_array = shape_get_grid(next_shape_index);

  for (row = 0; row < SHAPE_ROWS; ++row) {
    for (col = 0; col < SHAPE_COLUMNS; ++col) {

      grid_value = shape_array[row * SHAPE_COLUMNS + col];
      if (grid_value > 0) {
  	block.x = start_x + (col * BLOCK_SIZE);
  	block.y = start_y + (row * BLOCK_SIZE);
  	color_block = get_block_surface(display->images, grid_value, 0);
  	SDL_BlitSurface(color_block, NULL, display->screen, &block);
      }
    }
  }
}

void draw_grid(struct display_data *display, struct grid *grid, int start_x, int start_y) {
  SDL_Rect block;
  int row, col;
  unsigned char grid_value;
  SDL_Surface *color_block;

  //int animation_index = instance_get_animation_index();

  block.w = block.h = BLOCK_SIZE;

  for (row = 0; row < GRID_ROWS; ++row) {
    for (col = 0; col < GRID_COLUMNS; ++col) {

      grid_value = grid_get_block_value(grid, row, col);

      if (grid_value > 0) {

	block.x = start_x + (col * BLOCK_SIZE);
	block.y = start_y + (row * BLOCK_SIZE);

	color_block = get_block_surface(display->images, grid_value, 0);
	SDL_BlitSurface(color_block, NULL, display->screen, &block);
      }
    }
  }
}

SDL_Surface *get_block_surface(SDL_Surface **images, unsigned char value, int animation_index) {
  switch (value) {
  case 1:
    return images[PURPLE_BLOCK];
  case 2:
    return images[BLUE_BLOCK];
  case 3:
    return images[RED_BLOCK];
  case 4:
    return images[GREEN_BLOCK];
  case 5:
    return images[YELLOW_BLOCK];
  case 6:
    return images[ORANGE_BLOCK];
  case 7:
    return images[DARK_GREEN_BLOCK];
  case 8:
    return images[GRAY_BLOCK];//breaking_brick[animation_index];
  case 9:
    return images[GRAY_BLOCK];
  default:
    return NULL;
  }
}

void draw_text(struct display_data *display, const char *text, int start_x, int start_y, SDL_Color color) {

  SDL_Surface *text_surface;
  SDL_Rect dest_rect;

  text_surface = TTF_RenderText_Solid(display->font, text, color);
  if (text_surface == NULL) {
    return;
  }
  dest_rect.x = start_x;
  dest_rect.y = start_y;
  dest_rect.h = text_surface->h;
  dest_rect.w = text_surface->w;

  SDL_BlitSurface(text_surface, NULL, display->screen, &dest_rect);
  SDL_FreeSurface(text_surface);
}
