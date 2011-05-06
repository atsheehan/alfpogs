#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "SDL.h"
#include "menu.h"
#include "draw.h"
#include "game.h"
#include "input.h"

/* Structure used for initializing subsystems. */
struct init_system {
  bool (*init)(void);
  const char *system_name;
};

bool init(void);
void cleanup(void);

/* Program entry point. Initialize any subsystems and then
   enter into the main game loop. If anything goes wrong,
   clean up and go home. */
int main(int argc, char *argv[]) {

  /* Initialize any components here. */
  if (!init()) {
    cleanup();
    exit(1);
  }

  game_loop();

  cleanup();
  return 0;
}

/* Initializes any subsystems. */
bool init(void) {
  const int subsystem_count = 2;
  struct init_system subsystems[subsystem_count];
  subsystems[0].init = draw_init;
  subsystems[0].system_name = "drawing";
  subsystems[1].init = menu_init;
  subsystems[1].system_name = "menu";

  int i;
  for (i = 0; i < subsystem_count; ++i) {
    if (!subsystems[i].init()) {
      fprintf(stderr, "Error while initialize the %s subsystem.\n", subsystems[i].system_name);
      return false;
    }
  }

  return true;
}

/* Cleans up any resources from the various subsystems. */
void cleanup(void) {
  draw_cleanup();
}
