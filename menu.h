#ifndef MENU_H
#define MENU_H

#include "SDL.h"

#define HOST_NAME_SIZE 50

struct instance;

enum menu_pages {
  MAIN_MENU,
  SINGLE_PLAYER_MENU,
  MULTI_PLAYER_MENU,
  PAUSE_MENU
};

struct menu_entry {
  char *name;
  char *content;
  int content_size;
  void (*handler)(struct menu_entry *entry, struct instance *instance, SDLKey key);
};

struct menu_page {
  struct menu_entry *entries;
  int number_of_entries;
  int current_entry;
};

struct menu {
  struct menu_page *pages;
  int number_of_pages;
  enum menu_pages current_page;
};

char menu_init(struct menu *menu, struct instance *instance);
void menu_destroy(struct menu *menu);

void menu_next_entry(struct menu *menu);
void menu_prev_entry(struct menu *menu);
void menu_handle_input(struct menu *menu, struct instance *instance, SDLKey key);

#endif /* MENU_H */
