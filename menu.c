#include <string.h>
#include "menu.h"
#include "game.h"
#include "grid.h"
#include "client.h"
#include "SDL.h"


#define NUMBER_OF_MENUS 4
#define TOTAL_NUMBER_OF_ENTRIES 12

/* An array of all the menus to be used in the game. */
static struct menu menus[NUMBER_OF_MENUS];

/* An array of all menu entries used in the game. Each menu
   accesses various segments of this array. */
static struct menu_entry entries[TOTAL_NUMBER_OF_ENTRIES];

/* The index into the menus array for the menu currently in use. */
static int current_index;

/* Stores the starting level for a single player game. */
static int start_level;
static char level_buffer[10];

static void handler_resume_game(SDLKey key, char *content);
static void handler_go_back(SDLKey key, char *content);
static void handler_single_player(SDLKey key, char *content);
static void handler_multi_player(SDLKey key, char *content);
static void handler_quit(SDLKey key, char *content);
static void handler_start_game(SDLKey key, char *content);
static void handler_change_level(SDLKey key, char *content);
static void handler_do_nothing(SDLKey key, char *content);
static void handler_join_game(SDLKey key, char *content);

/* Sets the current menu. */
void menu_set_current(enum menu_type type) {

  /* The menus are indexed by the menu_type enum. */
  current_index = type;
}

/* Gets the current menu. */
struct menu *menu_get_current(void) {
  return &menus[current_index];
}

/* Handles input based on the currently selected entry. */
void menu_input_handler(SDLKey input) {
  struct menu *current_menu = &menus[current_index];
  struct menu_entry *current_entry = &current_menu->entries[current_menu->current_entry];

  current_entry->input_handler(input, current_entry->content);
}

/* Highlights the next entry in the current menu. */
void menu_next_entry(void) {
  struct menu *current_menu = &menus[current_index];

  if (current_menu->current_entry < (current_menu->number_of_entries - 1)) {
    ++current_menu->current_entry;
  }
}

/* Highlights the previous entry in the current menu. */
void menu_previous_entry(void) {
  struct menu *current_menu = &menus[current_index];

  if (current_menu->current_entry > 0) {
    --current_menu->current_entry;
  }
}

/* Initializes the menus to be used in the game. */
bool menu_init(void) {
  
  /* The game should start at the main menu. */
  current_index = MAIN;

  entries[0].name = "Single Player";
  entries[0].content = 0;
  entries[0].input_handler = handler_single_player;

  entries[1].name = "Multi Player";
  entries[1].content = 0;
  entries[1].input_handler = handler_multi_player;
  
  entries[2].name = "Quit";
  entries[2].content = 0;
  entries[2].input_handler = handler_quit;

  start_level = MIN_LEVEL;
  sprintf(level_buffer, "< %.2d >", start_level);

  entries[3].name = "Starting Level";
  entries[3].content = level_buffer;
  entries[3].input_handler = handler_change_level;

  entries[4].name = "Start Game";
  entries[4].content = 0;
  entries[4].input_handler = handler_start_game;
  
  entries[5].name = "Go Back";
  entries[5].content = 0;
  entries[5].input_handler = handler_go_back;

  entries[6].name = "Server";
  entries[6].content = 0;
  entries[6].input_handler = handler_do_nothing;

  entries[7].name = "Join Game";
  entries[7].content = 0;
  entries[7].input_handler = handler_join_game;
  
  entries[8].name = "Go Back";
  entries[8].content = 0;
  entries[8].input_handler = handler_go_back;

  entries[9].name = "Resume Game";
  entries[9].content = 0;
  entries[9].input_handler = handler_resume_game;

  entries[10].name = "Leave Game";
  entries[10].content = 0;
  entries[10].input_handler = handler_do_nothing;
  
  entries[11].name = "Quit";
  entries[11].content = 0;
  entries[11].input_handler = handler_quit;

  menus[MAIN].title = "AlfPogs";
  menus[MAIN].entries = &entries[0];
  menus[MAIN].number_of_entries = 3;
  menus[MAIN].current_entry = 0;
  
  menus[SINGLEPLAYER].title = "New Single-Player Game";
  menus[SINGLEPLAYER].entries = &entries[3];
  menus[SINGLEPLAYER].number_of_entries = 3;
  menus[SINGLEPLAYER].current_entry = 0;

  menus[MULTIPLAYER].title = "Join Multi-Player Game";
  menus[MULTIPLAYER].entries = &entries[6];
  menus[MULTIPLAYER].number_of_entries = 3;
  menus[MULTIPLAYER].current_entry = 0;

  menus[PAUSE].title = "Pause Menu";
  menus[PAUSE].entries = &entries[9];
  menus[PAUSE].number_of_entries = 3;
  menus[PAUSE].current_entry = 0;

  return true;
}

/* Input handler for the go back menu entry. Makes the main menu the current one. */
static void handler_go_back(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    current_index = MAIN;
  }
}

/* Changes the current menu to the single player menu. */
static void handler_single_player(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    current_index = SINGLEPLAYER;
  }
}

/* Changes the current menu to the multi-player menu. */
static void handler_multi_player(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    current_index = MULTIPLAYER;
  }
}

/* Starts a single player game and also sets the current menu to
   the pause menu. */
static void handler_start_game(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    game_state = PLAYING;
    current_index = PAUSE;
  }
}

/* Quits the application. */
static void handler_quit(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    game_state = EXITING;
  }
}

/* Adjusts the starting level for a single player game. */
static void handler_change_level(SDLKey key, char *content) {
  if (key == SDLK_LEFT) {
    if (start_level > MIN_LEVEL) {
      --start_level;
    }
  }
  if (key == SDLK_RIGHT) {
    if (start_level < MAX_LEVEL) {
      ++start_level;
    }
  }

  sprintf(level_buffer, "< %.2d >", start_level);
}

/* Leaves the pause menu and returns to the game. */
static void handler_resume_game(SDLKey key, char *content) {
  if (key == SDLK_RETURN) {
    game_state = PLAYING;
  }
}

/* Joins a multiplayer game. */
static void handler_join_game(SDLKey key, char *content) {
}

/* Exactly. */
static void handler_do_nothing(SDLKey key, char *content) {
}

