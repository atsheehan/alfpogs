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

char menu_init(struct menu *menu) {
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
  snprintf(entry->content, entry->content_size, "< %02d >", 1);
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
  entry->content_size = 7;
  entry->content = malloc(entry->content_size);
  if (entry->content == NULL) {
    fprintf(stderr, "cannot allocate memory for entry content\n");
    return 0;
  }
  snprintf(entry->content, entry->content_size, "< %02d >", 1);
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
    instance->game_type = SINGLE_PLAYER;
    instance->state = STATE_RUNNING;
    instance->num_players = 1;
  }
}

void menu_start_multi_game_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
}

void menu_set_level_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
}

void menu_set_host_handler(struct menu_entry *entry, struct instance *instance, SDLKey key) {
}
