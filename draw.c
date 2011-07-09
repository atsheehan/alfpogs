#include <stdlib.h>
#include <string.h>

#include "draw.h"
#include "grid.h"
#include "shape.h"
#include "instance.h"
#include "images.h"
#include "SDL_image.h"

#define BLOCK_SIZE 20
#define NEXT_SHAPE_DISPLAY_X 490
#define NEXT_SHAPE_DISPLAY_Y 150

#define P1_G1_GRID_TOP 40
#define P1_G1_GRID_LEFT 220

#define P1_G2_GRID_TOP 40
#define P1_G2_GRID_LEFT 115

#define P2_G2_GRID_TOP 40
#define P2_G2_GRID_LEFT 325


#define MASTER_IMAGE_FILENAME "images.png"

/* static void draw_next_shape(int next_shape_index); */
SDL_Surface *get_block_surface(SDL_Surface **images, int value, int animation_index);
void draw_grid(struct display_data *display, struct grid *instance, int start_x, int start_y);

bool draw_init(struct display_data *data) {

  data->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH, SDL_SWSURFACE);
  if (data->screen == NULL) {
    fprintf(stderr, "SDL_SetVideoMode: %s\n", SDL_GetError());
    return false;
  }

  data->images = images_load(MASTER_IMAGE_FILENAME);
  if (data->images == NULL) {
    fprintf(stderr, "could not load the images properly\n");
    return false;
  }

  data->black = SDL_MapRGB(data->screen->format, 0, 0, 0);
  return true;
}

/* Clean up any resources used by the drawing subsystem. */
void draw_cleanup(struct display_data *data) {
  images_free(data->images, NUMBER_OF_IMAGES);
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
    draw_grid(display, instance->grids[0], P1_G1_GRID_LEFT, P1_G1_GRID_TOP);
  } else {
    draw_grid(display, instance->grids[0], P1_G2_GRID_LEFT, P1_G2_GRID_TOP);
    draw_grid(display, instance->grids[1], P2_G2_GRID_LEFT, P2_G2_GRID_TOP);
  }

  /* draw_next_shape(instance_get_next_shape_index()); */
  /* sprintf(buffer, "%.7d", instance_get_score()); */
  /* draw_text(buffer, 60, 75, basic_font); */
  /* sprintf(buffer, "%.2d", instance_get_level()); */
  /* draw_text(buffer, 95, 165, basic_font); */
  /* sprintf(buffer, "%.7d", instance_get_lines_cleared());  */
  /* draw_text(buffer, 60, 255, basic_font); */

  /* char *message = instance_get_message(); */
  /* if (message != NULL) { */
  /*   strncpy(buffer, message, 50 - 1); */
  /*   buffer[49] = 0; */
  /*   draw_text(buffer, 0, 0, basic_font); */
  /* } */

  SDL_Flip(display->screen);
}

/* static void draw_next_shape(int next_shape_index) { */
/*   int i, j, row_index, grid_value; */
/*   SDL_Surface *color_block; */

/*   SDL_Rect block; */
/*   block.w = block.h = BLOCK_SIZE; */

/*   int *shape_array = shape_get_grid(next_shape_index); */
/*   for (i = 0; i < SHAPE_ROWS; ++i) { */
/*     row_index = i * SHAPE_COLUMNS; */

/*     for (j = 0; j < SHAPE_COLUMNS; ++j) { */
/*       grid_value = shape_array[row_index + j]; */
/*       if (grid_value > 0) { */
/*   	block.x = NEXT_SHAPE_DISPLAY_X + (j * BLOCK_SIZE); */
/*   	block.y = NEXT_SHAPE_DISPLAY_Y + (i * BLOCK_SIZE); */
/*   	color_block = get_color(grid_value, 0); */
/*   	SDL_BlitSurface(color_block, NULL, screen, &block); */
/*       } */
/*     } */
/*   } */
/* } */

void draw_grid(struct display_data *display, struct grid *grid, int start_x, int start_y) {
  SDL_Rect block;
  int row, col, grid_value;
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

SDL_Surface *get_block_surface(SDL_Surface **images, int value, int animation_index) {
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
