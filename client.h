#ifndef CLIENT_H
#define CLIENT_H

#include <stdbool.h>

/* The game client is an interface between the game client and the
   engine running the game. It is used to provide a uniform interface
   whether playing a local single-player game or accessing data over
   the network for a multiplayer game. */

struct grid_display {
  bool is_game_over;
  int *grid;
  int next_shape_index;
  int score;
  int level;
  int lines_cleared;
};

enum game_type {
  LOCAL,
  CLIENT,
  SERVER
};


struct game_details {
  int start_level;
  int number_of_players;
  enum game_type type;
  char server[100];
};

bool client_init(void);
void client_cleanup(void);
int client_get_details(int player_id, struct grid_display *details);
bool client_start_new_game(struct game_details *details);
void client_resume_game(void);
void client_pause_game(void);
void client_quit_game(void);
void client_move_left(void);
void client_move_right(void);
void client_move_down(void);
void client_rotate(void);
void client_drop(void);

#endif
