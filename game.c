#include "game.h"
#include "draw.h"
#include "input.h"
#include "menu.h"
#include "timer.h"
#include "SDL.h"
#include "SDL_thread.h"

/* The main game loop. Coordinates drawing to the screen, handling
   user input, and performing any other game logic. Runs in a loop
   until the game state is about to exit. */
void game_loop(void) {
  game_state = MENU;

  SDL_mutex *mutex = SDL_CreateMutex();
  SDL_mutexP(mutex);

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

    timer_wait_for_next_frame(mutex);
  }

  SDL_DestroyMutex(mutex);
}
