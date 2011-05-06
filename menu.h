#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "SDL.h"

/* A menu_entry represents a single listing within a menu. */
struct menu_entry {
  const char *name;		/* The name to display in the menu. */
  char *content; /* Additional content to display alongside the name. */
  void (*input_handler)(SDLKey, char *); /* How to handle input when this entry is highlighted. */
};

/* A menu is a collection of menu entries in a certain order. */
struct menu {
  const char *title;	      /* The title to display with the menu. */
  struct menu_entry *entries; /* An ordered array of menu entries. */
  int number_of_entries;      /* The total number of entries. */
  int current_entry;	   /* The currently highlighted menu entry. */
};

/* The menu_type enum is used to specify the different menus used in the game. */
enum menu_type {
  MAIN,
  SINGLEPLAYER,
  MULTIPLAYER,
  PAUSE
};

bool menu_init(void);
void menu_set_current(enum menu_type type);
struct menu *menu_get_current(void);
void menu_input_handler(SDLKey input);
void menu_next_entry(void);
void menu_previous_entry(void);

#endif /* MENU_H */
