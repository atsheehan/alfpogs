#ifndef LIST_H
#define LIST_H

struct list {
  struct node *first;
};

struct node {
  struct node *next;
  void *data;
};

struct list *list_create(void);
void list_destroy(struct list *list);
struct node *list_insert(struct list *list, void *data);


#endif /* LIST_H */
