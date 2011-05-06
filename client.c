#include <stdio.h>
#include "client.h"
#include "game.h"
#include "grid.h"
#include "server.h"
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_net.h"

static int client_run_local_game(void *start_level);
static int client_join_multiplayer_game(void *details);
static bool client_send_message(char *buffer, int length);

static enum game_type type;
static bool quit;
static bool paused;
static SDL_Thread *game_thread;
static TCPsocket server_socket;

bool client_init(void) {
  if (SDLNet_Init() < 0) {
    fprintf(stderr, "Error initializing SDL_net. Message: %s\n", SDLNet_GetError());
    return false;
  }

  return true;
}

void client_cleanup(void) {
  SDLNet_Quit();
}

int client_get_details(int player_id, struct grid_display *details) {
  return 0;
}

bool client_start_new_game(struct game_details *details) {
  if (details->start_level < MIN_LEVEL) {
    details->start_level = MIN_LEVEL;
  }
  if (details->start_level > MAX_LEVEL) {
    details->start_level = MAX_LEVEL;
  }

  quit = false;
  paused = false;
  type = details->type;

  switch (type) {
  case LOCAL:
    game_thread = SDL_CreateThread(client_run_local_game, details);
    break;

  case CLIENT:
    game_thread = SDL_CreateThread(client_join_multiplayer_game, details);
    break;

  case SERVER:
    game_thread = SDL_CreateThread(server_run_multiplayer_game, details);
    break;

  default:
    return false;
  }

  if (game_thread == NULL) {
    return false;
  }
  return true;
}

void client_resume_game(void) {
  paused = false;
}

void client_pause_game(void) {
  paused = true;
}

void client_quit_game(void) {
  int status;
  quit = true;
  SDL_WaitThread(game_thread, &status);
}

void client_move_left(void) {
  char buffer[5];

  switch (type) {
  case LOCAL:
    grid_move_shape_left(0);
    break;

  case CLIENT:
    strcpy(buffer, "LEFT");
    client_send_message(buffer, 5);
    break;

  default:
    break;
  }
}

void client_move_right(void) {
  grid_move_shape_right(0);
}

void client_move_down(void) {
  grid_move_shape_down(0);
}

void client_drop(void) {
  grid_drop_shape(0);
}

void client_rotate(void) {
  grid_rotate_shape(0);
}

static int client_run_local_game(void *_start_level) {
  Uint32 ticks_per_frame, next_frame_ticks;
  int start_level = *(int *)_start_level;

  ticks_per_frame = 1000 / FRAMES_PER_SECOND;
  next_frame_ticks = 0;

  grid_init(0, start_level);

  while (!quit) {

    if (!paused) {
      grid_update(0);
    }

    while (SDL_GetTicks() < next_frame_ticks);
    next_frame_ticks = SDL_GetTicks() + ticks_per_frame;
  }
  return 0;
}

static int client_join_multiplayer_game(void *_details) {
  int return_code = -1;
  char buffer[BUFFER_SIZE];
  IPaddress ip;

  struct game_details *details = (struct game_details *)_details;

  if (SDLNet_ResolveHost(&ip, details->server, PORT) < 0) {
    fprintf(stderr, "Error resolving host at %s on port %d. Message: %s\n", details->server, PORT, SDLNet_GetError());
    return return_code;
  }

  server_socket = SDLNet_TCP_Open(&ip);
  if (server_socket == NULL) {
    fprintf(stderr, "Error connecting to server. Message: %s\n", SDLNet_GetError());
    return return_code;
  }

  while (!quit) {
    if (SDLNet_TCP_Recv(server_socket, buffer, BUFFER_SIZE - 1) < 0) {
      fprintf(stderr, "Error receiving from server. Message: %s\n", SDLNet_GetError());
      quit = true;
    }
    
    fprintf(stdout, "Received %s\n", buffer);
  }

  SDLNet_TCP_Close(server_socket);
  return return_code;
}

static bool client_send_message(char *buffer, int length) {
  if (server_socket == NULL) {
    return false;
  }

  if (SDLNet_TCP_Send(server_socket, (void *)buffer, length) < length) {
    return false;
  }
  return true;
}
