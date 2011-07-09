#include "list.h"
#include <stdlib.h>

struct list *list_create(void) {
  struct list *new_list = malloc(sizeof(struct list));
  if (new_list == NULL) {
    return NULL;
  }

  new_list->first = NULL;
  return new_list;
}

void list_destroy(struct list *list) {
  struct node *node = list->first;
  while (node != NULL) {
    struct node *tmp = node;
    node = node->next;
    free(tmp);
  }
}

struct node *list_insert(struct list *list, void *data) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    return NULL;
  }

  new_node->data = data;
  new_node->next = list->first;
  list->first = new_node;

  return new_node;
}
