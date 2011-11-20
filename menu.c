#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "input.h"
#include "instance.h"

void menu_single_player_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_multi_player_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_quit_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_back_to_main_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_start_single_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_start_multi_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_set_level_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_set_host_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_leave_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);
void menu_resume_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event);

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
  strncpy(entry->content, instance->host, HOST_NAME_SIZE - 1);
  entry->content[HOST_NAME_SIZE - 1] = 0;
  entry->handler = menu_set_host_handler;

  entry = &page->entries[2];
  entry->name = "go back";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_back_to_main_handler;

  page = &menu->pages[PAUSE_MENU];

  page->number_of_entries = 3;
  page->current_entry = 0;
  page->entries = malloc(sizeof(struct menu_entry) * page->number_of_entries);
  if (page->entries == NULL) {
    fprintf(stderr, "cannot allocate memory for the page entries\n");
    return 0;
  }

  entry = &page->entries[0];
  entry->name = "resume game";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_resume_game_handler;

  entry = &page->entries[1];
  entry->name = "leave game";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_leave_game_handler;

  entry = &page->entries[2];
  entry->name = "quit";
  entry->content = NULL;
  entry->content_size = 0;
  entry->handler = menu_quit_game_handler;

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

void menu_handle_input(struct menu *menu, struct instance *instance, enum input_event event) {
  struct menu_page *page;
  struct menu_entry *entry;

  page = &menu->pages[menu->current_page];
  entry = &page->entries[page->current_entry];
  
  entry->handler(entry, instance, event);
}

void menu_single_player_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    instance->menu.current_page = SINGLE_PLAYER_MENU;
  }
}

void menu_multi_player_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    instance->menu.current_page = MULTI_PLAYER_MENU;
  }
}

void menu_quit_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    instance->state = STATE_QUITTING;
  }
}

void menu_back_to_main_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    instance->menu.current_page = MAIN_MENU;
  }
}

void menu_start_single_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    instance_single_player_init(instance);
    instance->state = STATE_RUNNING;
  }
}

void menu_start_multi_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_BUTTON_1) {
    if (!instance_multi_player_init(instance)) {
      fprintf(stderr, "could not initialize the multi player instance\n");
      return;
    }
    instance->state = STATE_RUNNING;
  }
}

void menu_set_level_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  if (event == INPUT_RIGHT) {
    if (instance->starting_level >= MAX_LEVEL) {
      instance->starting_level = MAX_LEVEL;
    } else {
      instance->starting_level++;
    }
  }

  if (event == INPUT_LEFT) {
    if (instance->starting_level <= MIN_LEVEL) {
      instance->starting_level = MIN_LEVEL;
    } else {
      instance->starting_level--;
    }
  }

  sprintf(entry->content, "< %02d >", instance->starting_level);
}

void menu_set_host_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  /* int length; */

  /* length = strlen(instance->host); */

  /* if ((key == SDLK_BACKSPACE || key == SDLK_DELETE) && */
  /*     length > 0) { */

  /*   instance->host[length - 1] = 0; */
  /* } else { */

  /*   if (length < HOST_NAME_SIZE - 1) { */
  /*     instance->host[length] = menu_get_char_from_key(key); */
  /*     instance->host[length + 1] = 0; */
  /*   } */
  /* } */

  /* strncpy(entry->content, instance->host, entry->content_size - 1); */
}

void menu_leave_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  instance->menu.current_page = MAIN_MENU;
  // kill instance
  // send quit message if multiplayer game
}

void menu_resume_game_handler(struct menu_entry *entry, struct instance *instance, enum input_event event) {
  instance->state = STATE_RUNNING;
  // send resume message for multi?
}
