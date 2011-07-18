#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

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

  page->number_of_entries = 2;
  page->current_entry = 0;
  page->entries = malloc(sizeof(struct menu_entry) * page->number_of_entries);
  if (page->entries == NULL) {
    fprintf(stderr, "cannot allocate memory for the page entries\n");
    return 0;
  }
  
  entry = &page->entries[0];
  entry->name = "hello, world";

  entry = &page->entries[1];
  entry->name = "goodbye, world";

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
