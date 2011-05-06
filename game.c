#include "game.h"
#include "draw.h"
#include "input.h"
#include "menu.h"
#include "SDL.h"

/* The main game loop. Coordinates drawing to the screen, handling
   user input, and performing any other game logic. Runs in a loop
   until the game state is about to exit. */
void game_loop(void) {
  Uint32 last_frame_ticks = 0;
  Uint32 ticks_per_frame = 1000 / FRAMES_PER_SECOND;
  game_state = MENU;

  struct grid grid;
  grid_init(&grid, 1);

  while (game_state != EXITING) {
    switch (game_state) {
    case MENU:
      input_menu();
      draw_menu(menu_get_current());
      break;

    case PLAYING:
      input_game(&grid);
      draw_game(&grid);
      grid_update(&grid);
      break;

    default:
      game_state = EXITING;
      break;
    }

    while (SDL_GetTicks() < last_frame_ticks + ticks_per_frame);
    last_frame_ticks = SDL_GetTicks();
  }
}
