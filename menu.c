#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "instance.h"

void menu_single_player_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_multi_player_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_quit_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_back_to_main_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_start_single_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_start_multi_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_set_level_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
void menu_set_host_handler(struct menu_entry *entry, struct instance *instance, SDLKey key);
char menu_get_char_from_key(SDLKey key);

char menu_init(struct menu *menu, struct instance *instance) {
  struct menu_page *page;
  struct menu_entry *entry;

  menu->current_page = MAIN_MENU;
  menu->number_of_pages = 4;

  menu->pages = malloc(sizeof(struct menu_page) * menu->number_of_pages);
  if (menu->pages == NULL) {
    fprintf(stderr, "cannot allocate memory for the menu pages\n");
    return 0;
  }

  page = &menu->pages[MAIN_MENU];

  page->number_of_entries = 3;
  page->current_entry = 0;
  page->entries = malloc(sizeof(struct menu_entry) * page->number_of_entries);
  if (page->entries == NULL) {
    fprintf(stderr, "cannot allocate memory for the page entries\n");
    return 0;
  }
  
  entry = &page->entries[0];
  entry->name = "single player";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_single_player_game_handler;

  entry = &page->entries[1];
  entry->name = "multi player";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_multi_player_game_handler;

  entry = &page->entries[2];
  entry->name = "quit";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_quit_game_handler;

  page = &menu->pages[SINGLE_PLAYER_MENU];

  page->number_of_entries = 3;
  page->current_entry = 0;
  page->entries = malloc(sizeof(struct menu_entry) * page->number_of_entries);
  if (page->entries == NULL) {
    fprintf(stderr, "cannot allocate memory for the page entries\n");
    return 0;
  }

  entry = &page->entries[0];
  entry->name = "start game";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_start_single_game_handler;

  entry = &page->entries[1];
  entry->name = "level";
  entry->content_size = 7;
  entry->content = malloc(entry->content_size);
  if (entry->content == NULL) {
    fprintf(stderr, "cannot allocate memory for entry content\n");
    return 0;
  }
  sprintf(entry->content, "< %02d >", 1);
  entry->handler = menu_set_level_handler;

  entry = &page->entries[2];
  entry->name = "go back";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_back_to_main_handler;

  page = &menu->pages[MULTI_PLAYER_MENU];

  page->number_of_entries = 3;
  page->current_entry = 0;
  page->entries = malloc(sizeof(struct menu_entry) * page->number_of_entries);
  if (page->entries == NULL) {
    fprintf(stderr, "cannot allocate memory for the page entries\n");
    return 0;
  }

  entry = &page->entries[0];
  entry->name = "join game";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_start_multi_game_handler;

  entry = &page->entries[1];
  entry->name = "host";
  entry->content_size = HOST_NAME_SIZE;
  entry->content = malloc(entry->content_size);
  if (entry->content == NULL) {
    fprintf(stderr, "cannot allocate memory for entry content\n");
    return 0;
  }
  entry->content[0] = '\0';
  entry->handler = menu_set_host_handler;

  entry = &page->entries[2];
  entry->name = "go back";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_back_to_main_handler;

  return 1;
}

void menu_destroy(struct menu *menu) {

}

void menu_next_entry(struct menu *menu) {
  struct menu_page *page;

  page = &menu->pages[menu->current_page];
  page->current_entry++;

  if (page->current_entry >= page->number_of_entries) {
    page->current_entry = 0;
  }
}

void menu_prev_entry(struct menu *menu) {
  struct menu_page *page;

  page = &menu->pages[menu->current_page];
  page->current_entry--;

  if (page->current_entry < 0) {
    page->current_entry = page->number_of_entries - 1;
  }
}

void menu_handle_input(struct menu *menu, struct instance *instance, SDLKey key) {
  struct menu_page *page;
  struct menu_entry *entry;

  page = &menu->pages[menu->current_page];
  entry = &page->entries[page->current_entry];
  
  entry->handler(entry, instance, key);
}

void menu_single_player_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    instance->menu.current_page = SINGLE_PLAYER_MENU;
  }
}

void menu_multi_player_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    instance->menu.current_page = MULTI_PLAYER_MENU;
  }
}

void menu_quit_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    instance->state = STATE_QUITTING;
  }
}

void menu_back_to_main_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    instance->menu.current_page = MAIN_MENU;
  }
}

void menu_start_single_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    instance_single_player_init(instance);
    instance->state = STATE_RUNNING;
  }
}

void menu_start_multi_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RETURN) {
    if (!instance_multi_player_init(instance)) {
      fprintf(stderr, "could not initialize the multi player instance\n");
      return;
    }
    instance->state = STATE_RUNNING;
  }
}

void menu_set_level_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  if (key == SDLK_RIGHT) {
    if (instance->starting_level >= MAX_LEVEL) {
      instance->starting_level = MAX_LEVEL;
    } else {
      instance->starting_level++;
    }
  }

  if (key == SDLK_LEFT) {
    if (instance->starting_level <= MIN_LEVEL) {
      instance->starting_level = MIN_LEVEL;
    } else {
      instance->starting_level--;
    }
  }

  sprintf(entry->content, "< %02d >", instance->starting_level);
}

void menu_set_host_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
  int length;

  length = strlen(instance->host);

  if ((key == SDLK_BACKSPACE || key == SDLK_DELETE) &&
      length > 0) {

    instance->host[length - 1] = 0;
  } else {

    if (length < HOST_NAME_SIZE - 1) {
      instance->host[length] = menu_get_char_from_key(key);
      instance->host[length + 1] = 0;
    }
  }

  strncpy(entry->content, instance->host, entry->content_size - 1);
}

char menu_get_char_from_key(SDLKey key) {
  switch (key) {
  case SDLK_a: return 'a';
  case SDLK_b: return 'b';
  case SDLK_c: return 'c';
  case SDLK_d: return 'd';
  case SDLK_e: return 'e';
  case SDLK_f: return 'f';
  case SDLK_g: return 'g';
  case SDLK_h: return 'h';
  case SDLK_i: return 'i';
  case SDLK_j: return 'j';
  case SDLK_k: return 'k';
  case SDLK_l: return 'l';
  case SDLK_m: return 'm';
  case SDLK_n: return 'n';
  case SDLK_o: return 'o';
  case SDLK_p: return 'p';
  case SDLK_q: return 'q';
  case SDLK_r: return 'r';
  case SDLK_s: return 's';
  case SDLK_t: return 't';
  case SDLK_u: return 'u';
  case SDLK_v: return 'v';
  case SDLK_w: return 'w';
  case SDLK_x: return 'x';
  case SDLK_y: return 'y';
  case SDLK_z: return 'z';
  case SDLK_0: return '0';
  case SDLK_1: return '1';
  case SDLK_2: return '2';
  case SDLK_3: return '3';
  case SDLK_4: return '4';
  case SDLK_5: return '5';
  case SDLK_6: return '6';
  case SDLK_7: return '7';
  case SDLK_8: return '8';
  case SDLK_9: return '9';
  case SDLK_KP0: return '0';
  case SDLK_KP1: return '1';
  case SDLK_KP2: return '2';
  case SDLK_KP3: return '3';
  case SDLK_KP4: return '4';
  case SDLK_KP5: return '5';
  case SDLK_KP6: return '6';
  case SDLK_KP7: return '7';
  case SDLK_KP8: return '8';
  case SDLK_KP9: return '9';
  case SDLK_KP_PERIOD: return '.';
  case SDLK_KP_DIVIDE: return '/';
  case SDLK_KP_MULTIPLY: return '*';
  case SDLK_KP_MINUS: return '-';
  case SDLK_KP_PLUS: return '+';
  case SDLK_KP_EQUALS: return '=';
  case SDLK_PERIOD: return '.';
  case SDLK_EXCLAIM: return '!';
  case SDLK_QUOTEDBL: return '"';
  case SDLK_HASH: return '#';
  case SDLK_DOLLAR: return '$';
  case SDLK_AMPERSAND: return '&';
  case SDLK_QUOTE: return '\\';
  case SDLK_LEFTPAREN: return '(';
  case SDLK_RIGHTPAREN: return ')';
  case SDLK_ASTERISK: return '*';
  case SDLK_PLUS: return '+';
  case SDLK_COMMA: return ',';
  case SDLK_SLASH: return '/';
  case SDLK_SPACE: return ' ';
  default: return 0;
  }
}
