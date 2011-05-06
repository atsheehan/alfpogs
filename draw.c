#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "menu.h"
#include "grid.h"
#include "shape.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define BLOCK_SIZE 20
#define BASIC_FONT "font.ttf"
#define BASIC_FONT_SIZE 24
#define MENU_FONT_SIZE 36
#define NEXT_SHAPE_DISPLAY_X 490
#define NEXT_SHAPE_DISPLAY_Y 150

static TTF_Font *basic_font;
static TTF_Font *menu_font;

static Uint32 black;
static Uint32 white;

static SDL_Surface *background;
static SDL_Surface *green_block;
static SDL_Surface *blue_block;
static SDL_Surface *red_block;
static SDL_Surface *orange_block;
static SDL_Surface *yellow_block;
static SDL_Surface *purple_block;
static SDL_Surface *gray_block;
static SDL_Surface *dark_green_block;
static SDL_Surface *menu_background;
static SDL_Surface *breaking_brick[BREAKING_BRICK_FRAMES];

static int grid_top;
static int grid_left;

static void draw_grid(struct grid *grid);
static void draw_next_shape(int next_shape_index);
static SDL_Surface *get_color(int value, int animation_index);
static void draw_text(const char *text, int x, int y, TTF_Font *font);
static void draw_text_centered(const char *text, int x, int y, TTF_Font *font);
static int load_surfaces(void);
static void free_surfaces(void);

/* Initializes anything needed to start drawing on the
   screen. Returns 0 on failure. */
bool draw_init(void) {
  screen = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "unable to init SDL: %s\n", SDL_GetError());
    return false;
  }
  atexit(SDL_Quit);
  
  if (TTF_Init() < 0) {
    fprintf(stderr, "unable to init TTF: %s\n", TTF_GetError());
    return false;
  }

  basic_font = TTF_OpenFont(BASIC_FONT, BASIC_FONT_SIZE);
  if (basic_font == NULL) {
    fprintf(stderr, "unable to load font %s\n", BASIC_FONT);
    return false;
  }

  menu_font = TTF_OpenFont(BASIC_FONT, MENU_FONT_SIZE);
  if (menu_font == NULL) {
    fprintf(stderr, "unable to load font %s\n", BASIC_FONT);
    return false;
  }

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BIT_DEPTH, SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, "unable to set the video: %s\n", SDL_GetError());
    return false;
  }

  if (!load_surfaces()) {
    fprintf(stderr, "unable to load images from disk\n");
    return false;
  }

  /* Calculate the location of certain items to draw. */
  grid_top = (SCREEN_HEIGHT - (GRID_ROWS * BLOCK_SIZE)) / 2;
  grid_left = (SCREEN_WIDTH - (GRID_COLUMNS * BLOCK_SIZE)) / 2;

  /* Save the colors based on their RGB values. */
  black = SDL_MapRGB(screen->format, 0, 0, 0);
  white = SDL_MapRGB(screen->format, 255, 255, 255);

  return true;
}

/* Clean up any resources used by the drawing subsystem. */
void draw_cleanup(void) {
  free_surfaces();

  if (screen != NULL) {
    SDL_FreeSurface(screen);
    screen = NULL;
  }

  if (menu_font != NULL) {
    TTF_CloseFont(menu_font);
    menu_font = NULL;
  }  

  if (basic_font != NULL) {
    TTF_CloseFont(basic_font);
    basic_font = NULL;
  }

  if (TTF_WasInit()) {
    TTF_Quit();
  }
}

/* Draws any graphics to the screen while in the menu. */
void draw_menu(struct menu *menu) {
  SDL_FillRect(screen, NULL, black);
  SDL_BlitSurface(menu_background, NULL, screen, NULL);

  int i;
  for (i = 0; i < menu->number_of_entries; ++i) {
    draw_text_centered(menu->entries[i].name, SCREEN_WIDTH / 2, 200 + (i * 50), menu_font);
    if (i == menu->current_entry) {
      draw_text_centered("*", SCREEN_WIDTH / 4, 200 + (i * 50), menu_font);
    }
    if (menu->entries[i].content != NULL) {
      draw_text_centered(menu->entries[i].content, SCREEN_WIDTH * 3 / 4, 200 + (i * 50), menu_font);
    }
  }
  SDL_Flip(screen);
}

/* Draws any graphics to the screen while playing the game. */
void draw_game(struct grid *grid) {
  char buffer[50];

  SDL_FillRect(screen, NULL, black);

  SDL_BlitSurface(background, NULL, screen, NULL);
  draw_grid(grid);
  draw_next_shape(grid->next_shape_index);
  sprintf(buffer, "%.7d", grid->score);
  draw_text(buffer, 60, 75, basic_font);
  sprintf(buffer, "%.2d", grid->level);
  draw_text(buffer, 95, 165, basic_font);
  sprintf(buffer, "%.7d", grid->lines_cleared); 
  draw_text(buffer, 60, 255, basic_font);

  SDL_Flip(screen);
}

static void draw_next_shape(int next_shape_index) {
  int i, j, row_index, grid_value;
  SDL_Surface *color_block;

  SDL_Rect block;
  block.w = block.h = BLOCK_SIZE;

  int *shape_array = shape_get_grid(next_shape_index);
  for (i = 0; i < SHAPE_ROWS; ++i) {
    row_index = i * SHAPE_COLUMNS;

    for (j = 0; j < SHAPE_COLUMNS; ++j) {
      grid_value = shape_array[row_index + j];
      if (grid_value > 0) {
  	block.x = NEXT_SHAPE_DISPLAY_X + (j * BLOCK_SIZE);
  	block.y = NEXT_SHAPE_DISPLAY_Y + (i * BLOCK_SIZE);
  	color_block = get_color(grid_value, 0);
  	SDL_BlitSurface(color_block, NULL, screen, &block);
      }
    }
  }
}

static void draw_grid(struct grid *grid) {
  SDL_Rect block;
  int row, col, grid_value;
  SDL_Surface *color_block;

  block.w = block.h = BLOCK_SIZE;

  for (row = 0; row < GRID_ROWS; ++row) {
    for (col = 0; col < GRID_COLUMNS; ++col) {
      grid_value = grid_get_block_value(grid, row, col);
      if (grid_value > 0) {
	block.x = grid_left + (col * BLOCK_SIZE);
	block.y = grid_top + (row * BLOCK_SIZE);
	color_block = get_color(grid_value, grid->animation_index);
	SDL_BlitSurface(color_block, NULL, screen, &block);
      }
    }
  }
}

static SDL_Surface *get_color(int value, int animation_index) {
  switch (value) {
  case 1:
    return purple_block;
  case 2:
    return blue_block;
  case 3:
    return red_block;
  case 4:
    return green_block;
  case 5:
    return yellow_block;
  case 6:
    return orange_block;
  case 7:
    return dark_green_block;
  case 8:
    return breaking_brick[animation_index];
  case 9:
    return gray_block;
  default:
    return NULL;
  }
}

static void draw_text(const char *text, int x, int y, TTF_Font *font) {
  SDL_Color color = {255, 255, 255};
  SDL_Surface *text_surface = NULL;
  SDL_Rect dest_rect;

  text_surface = TTF_RenderText_Solid(font, text, color);
  if (text_surface == NULL) {
    return;
  }

  dest_rect.x = x;
  dest_rect.y = y;
  dest_rect.h = text_surface->h;
  dest_rect.w = text_surface->w;
  SDL_BlitSurface(text_surface, NULL, screen, &dest_rect);
  SDL_FreeSurface(text_surface);
}

static void draw_text_centered(const char *text, int x, int y, TTF_Font *font) {
  SDL_Color color = {255, 255, 255};
  SDL_Surface *text_surface = NULL;
  SDL_Rect dest_rect;

  text_surface = TTF_RenderText_Solid(font, text, color);
  if (text_surface == NULL) {
    return;
  }

  dest_rect.x = x - (text_surface->w / 2);
  dest_rect.y = y - (text_surface->h / 2);
  dest_rect.h = text_surface->h;
  dest_rect.w = text_surface->w;
  SDL_BlitSurface(text_surface, NULL, screen, &dest_rect);
  SDL_FreeSurface(text_surface);
}

static int load_surfaces(void) {
  SDL_Rect source_rect;
  int i;
  SDL_Surface *all_images = IMG_Load("images.png");
  if (all_images == NULL) {
    fprintf(stderr, "could not load the images bitmap: %s\n", IMG_GetError());
    return 0;
  }

  background = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 480, 32, 0, 0, 0, 0);
  if (background == NULL) {
    fprintf(stderr, "could not create the background surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(background, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 255, 0, 255));

  source_rect.w = 640;
  source_rect.h = 480;
  source_rect.x = source_rect.y = 0;
  if (SDL_BlitSurface(all_images, &source_rect, background, NULL) == -1) {
    fprintf(stderr, "could not blit the background: %s\n", SDL_GetError());
    return 0;
  }

  menu_background = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 480, 32, 0, 0, 0, 0);
  if (menu_background == NULL) {
    fprintf(stderr, "could not create the menu_background surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(menu_background, SDL_SRCCOLORKEY, SDL_MapRGB(menu_background->format, 255, 0, 255));

  source_rect.w = 640;
  source_rect.h = 480;
  source_rect.x = 0;
  source_rect.y = 520;
  if (SDL_BlitSurface(all_images, &source_rect, menu_background, NULL) == -1) {
    fprintf(stderr, "could not blit the menu_background: %s\n", SDL_GetError());
    return 0;
  }

  red_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (red_block == NULL) {
    fprintf(stderr, "could not create the red_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(red_block, SDL_SRCCOLORKEY, SDL_MapRGB(red_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 0;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, red_block, NULL) == -1) {
    fprintf(stderr, "could not blit the red_block: %s\n", SDL_GetError());
    return 0;
  }

  green_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (green_block == NULL) {
    fprintf(stderr, "could not create the green_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(green_block, SDL_SRCCOLORKEY, SDL_MapRGB(green_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 20;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, green_block, NULL) == -1) {
    fprintf(stderr, "could not blit the green_block: %s\n", SDL_GetError());
    return 0;
  }

  blue_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (blue_block == NULL) {
    fprintf(stderr, "could not create the blue_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(blue_block, SDL_SRCCOLORKEY, SDL_MapRGB(blue_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 40;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, blue_block, NULL) == -1) {
    fprintf(stderr, "could not blit the blue_block: %s\n", SDL_GetError());
    return 0;
  }

  yellow_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (yellow_block == NULL) {
    fprintf(stderr, "could not create the yellow_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(yellow_block, SDL_SRCCOLORKEY, SDL_MapRGB(yellow_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 60;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, yellow_block, NULL) == -1) {
    fprintf(stderr, "could not blit the yellow_block: %s\n", SDL_GetError());
    return 0;
  }

  orange_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (orange_block == NULL) {
    fprintf(stderr, "could not create the orange_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(orange_block, SDL_SRCCOLORKEY, SDL_MapRGB(orange_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 80;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, orange_block, NULL) == -1) {
    fprintf(stderr, "could not blit the orange_block: %s\n", SDL_GetError());
    return 0;
  }

  purple_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (purple_block == NULL) {
    fprintf(stderr, "could not create the purple_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(purple_block, SDL_SRCCOLORKEY, SDL_MapRGB(purple_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 100;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, purple_block, NULL) == -1) {
    fprintf(stderr, "could not blit the purple_block: %s\n", SDL_GetError());
    return 0;
  }

  dark_green_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (dark_green_block == NULL) {
    fprintf(stderr, "could not create the dark_green_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(dark_green_block, SDL_SRCCOLORKEY, SDL_MapRGB(dark_green_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 120;
  source_rect.y = 480;
  if (SDL_BlitSurface(all_images, &source_rect, dark_green_block, NULL) == -1) {
    fprintf(stderr, "could not blit the dark_green_block: %s\n", SDL_GetError());
    return 0;
  }

  gray_block = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
  if (gray_block == NULL) {
    fprintf(stderr, "could not create the gray_block surface: %s\n", SDL_GetError());
    return 0;
  }
  SDL_SetColorKey(gray_block, SDL_SRCCOLORKEY, SDL_MapRGB(gray_block->format, 255, 0, 255));
  
  source_rect.w = 20;
  source_rect.h = 20;
  source_rect.x = 0;
  source_rect.y = 500;
  if (SDL_BlitSurface(all_images, &source_rect, gray_block, NULL) == -1) {
    fprintf(stderr, "could not blit the gray_block: %s\n", SDL_GetError());
    return 0;
  }


  for (i = 0; i < BREAKING_BRICK_FRAMES; ++i) {
    breaking_brick[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, 20, 20, 32, 0, 0, 0, 0);
    if (breaking_brick[i] == NULL) {
      fprintf(stderr, "could not create the breaking_brick[%d] surface: %s\n", i, SDL_GetError());
      return 0;
    }
    SDL_SetColorKey(breaking_brick[i], SDL_SRCCOLORKEY, SDL_MapRGB(breaking_brick[i]->format, 255, 0, 255));
  
    source_rect.w = 20;
    source_rect.h = 20;
    source_rect.x = i * 20;
    source_rect.y = 500;
    if (SDL_BlitSurface(all_images, &source_rect, breaking_brick[i], NULL) == -1) {
      fprintf(stderr, "could not blit the breaking_brick[%d]: %s\n", i, SDL_GetError());
      return 0;
    }
  }

  SDL_FreeSurface(all_images);
  all_images = NULL;

  return 1;
}

static void free_surfaces(void) {
  int i;

  if (background != NULL) {
    SDL_FreeSurface(background);
  }

  if (green_block != NULL) {
    SDL_FreeSurface(green_block);
  }

  if (blue_block != NULL) {
    SDL_FreeSurface(blue_block);
  }

  if (yellow_block != NULL) {
    SDL_FreeSurface(yellow_block);
  }

  if (red_block != NULL) {
    SDL_FreeSurface(red_block);
  }

  if (orange_block != NULL) {
    SDL_FreeSurface(orange_block);
  }

  if (purple_block != NULL) {
    SDL_FreeSurface(purple_block);
  }

  if (dark_green_block != NULL) {
    SDL_FreeSurface(dark_green_block);
  }

  if (gray_block != NULL) {
    SDL_FreeSurface(gray_block);
  }

  if (menu_background != NULL) {
    SDL_FreeSurface(menu_background);
  }


  for (i = 0; i < BREAKING_BRICK_FRAMES; ++i) {
    if (breaking_brick[i] != NULL) {
      SDL_FreeSurface(breaking_brick[i]);
    }
  }
}

