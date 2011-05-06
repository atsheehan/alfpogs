#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "grid.h"
#include "game.h"
#include "SDL_net.h"
#include "SDL_thread.h"



static int number_of_players;
static TCPsocket sockets[MAX_PLAYER_COUNT];
static SDL_Thread *listen_threads[MAX_PLAYER_COUNT];
static bool quit;

static bool wait_for_connections(void);
static int server_listen(void *_player_id);
static bool server_send_message(int player_id, char *buffer, int length);
static void server_send_update(int player_id);


bool server_init(void) {
  if (SDLNet_Init() < 0) {
    fprintf(stderr, "Error initializing SDL_net. Message: %s\n", SDLNet_GetError());
    return false;
  }

  number_of_players = 1;

  return true;
}

void server_cleanup(void) {
  SDLNet_Quit();
}

int server_run_multiplayer_game(void *_details) {
  int i;
  for (i = 0; i < number_of_players; ++i) {
    grid_init(i, 1);
  }

  if (!wait_for_connections()) {
    return -1;
  }

  Uint32 ticks_per_frame, next_frame_ticks;
  ticks_per_frame = 1000 / FRAMES_PER_SECOND;
  next_frame_ticks = 0;

  while (!quit) {

    for (i = 0; i < number_of_players; ++i) {
      grid_update(i);
      server_send_update(i);
    }

    while (SDL_GetTicks() < next_frame_ticks);
    next_frame_ticks = SDL_GetTicks() + ticks_per_frame;
  }
  return 0;
}

static bool wait_for_connections(void) {
  IPaddress ip;
  TCPsocket server_socket;
  
  if (SDLNet_ResolveHost(&ip, NULL, PORT) < 0) {
    fprintf(stderr, "Error resolving host. Message: %s\n", SDLNet_GetError());
    return false;
  }

  server_socket = SDLNet_TCP_Open(&ip);
  if (server_socket == NULL) {
    fprintf(stderr, "Error listening on port %d. Message: %s\n", PORT, SDLNet_GetError());
    return false;
  }

  int i;
  for (i = 0; i < number_of_players; ++i) {
    while (!quit) {
      sockets[i] = SDLNet_TCP_Accept(server_socket);
      if (sockets[i] != NULL) {
	void *p;
	memcpy(&p, &i, sizeof(i));
	listen_threads[i] = SDL_CreateThread(server_listen, p);
	break;
      }
    }
  }

  return true;
}

static int server_listen(void *_player_id) {
  char buffer[BUFFER_SIZE];
  int player_id;
  memcpy(&player_id, &_player_id, sizeof(player_id));
  fprintf(stdout, "Server listening for player_id %d\n", player_id);

  if (player_id < 0 || player_id >= number_of_players) {
    return -1;
  }

  while (!quit) {
    if (SDLNet_TCP_Recv(sockets[player_id], buffer, BUFFER_SIZE - 1) == -1) {
      return -1;
    }

    fprintf(stdout, "Message received from %d: %s\n", player_id, buffer);
  }

  return 0;
}

static bool server_send_message(int player_id, char *buffer, int length) {
  if (sockets[player_id] == NULL) {
    return false;
  }

  if (SDLNet_TCP_Send(sockets[player_id], (void *)buffer, length) < length) {
    return false;
  }
  return true;
}

static void server_send_update(int player_id) {
  int buffer_size = GRID_SIZE + 5;
  int buffer[buffer_size];

  int *grid = grid_get_display(player_id);
  memcpy(buffer, grid, GRID_SIZE * sizeof(int));

  server_send_message(player_id, (char *)buffer, buffer_size * sizeof(int));
}
