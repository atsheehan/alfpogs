#include "input.h"
#include "menu.h"
#include "game.h"
#include "SDL.h"

static SDL_Event event;

/* Handles user input in the menu state. */
void input_menu(void) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_UP) {
	menu_previous_entry();
      } else if (event.key.keysym.sym == SDLK_DOWN) {
	menu_next_entry();
      } else {
	menu_input_handler(event.key.keysym.sym);
      }
      break;

    case SDL_QUIT:
      game_state = EXITING;
      break;
    }
  }
}

/* Handles user input while the game is running. */
void input_game(struct grid *grid) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
	grid_move_shape_left(grid);
	break;
      case SDLK_RIGHT:
	grid_move_shape_right(grid);
	break;
      case SDLK_DOWN:
	grid_move_shape_down(grid);
	break;
      case SDLK_SPACE:
	grid_rotate_shape(grid);
	break;
      case SDLK_UP:
	grid_drop_shape(grid);
	break;
      case SDLK_ESCAPE:
	game_state = MENU;
      default:
	break;
      }
      break;

    case SDL_QUIT:
      game_state = EXITING;
      break;
    }
  }
}
