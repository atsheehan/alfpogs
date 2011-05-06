#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define FRAMES_PER_SECOND 60

enum state {
  MENU,
  PLAYING,
  EXITING,
};

/* Used to determine what part of the game the program is
   running. */
enum state game_state;

void game_loop(void);

#endif /* GAME_H */
