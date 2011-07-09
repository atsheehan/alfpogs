#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "net.h"
#include "grid.h"
#include "list.h"
#include "SDL.h"
#include "SDL_thread.h"

#define MAX_BUFFER_SIZE 500

struct connection {
  struct sockaddr_in address;
  bool has_left;
  bool in_instance;
  char event;
};

struct new_instance_params {
  struct connection **connections;
  int num_players;
  SDL_cond *sync_condition;
  int sd;
};

struct watchdog_params {
  struct list *connection_list;
  sem_t *connection_list_sem;
  bool *quitting;
  SDL_cond *sync_condition;
  int sd;
};

void *new_instance_func(void *_params);
Uint32 sync_framerate_func(Uint32 interval, void *_condition);
void *watchdog_func(void *_params);
struct connection *find_connection(struct sockaddr_in *address, struct list *connection_list);

int main() {

  int sd;
  int message_size;
  char recv_buffer[MAX_BUFFER_SIZE];
  char send_buffer[MAX_BUFFER_SIZE];
  struct sockaddr_in local_address;
  struct sockaddr_in client_address;
  unsigned int client_address_length;
  bool quitting = false;
  struct list *connection_list = list_create();

  sem_t connection_list_sem;
  sem_init(&connection_list_sem, 0, 1);

  if (SDL_Init(SDL_INIT_TIMER) == -1) {
    fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_cond *sync_condition = SDL_CreateCond();
  if (sync_condition == NULL) {
    fprintf(stderr, "SDL_CreateCond: %s\n", SDL_GetError());
    exit(1);
  }

  Uint32 interval = 1000 / 30;
  SDL_TimerID timer_id = SDL_AddTimer(interval, sync_framerate_func, sync_condition);
  if (timer_id == NULL) {
    fprintf(stderr, "SDL_AddTimer: %s\n", SDL_GetError());
    exit(1);
  }

  sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sd == -1) {
    perror("socket");
    exit(1);
  }

  local_address.sin_family = AF_INET;
  local_address.sin_addr.s_addr = htonl(INADDR_ANY);
  local_address.sin_port = htons(4485);

  if (bind(sd, (struct sockaddr *)&local_address, sizeof(local_address)) == -1) {
    perror("bind");
    close(sd);
    exit(1);
  }

  // start the watchdog
  struct watchdog_params watchdog_params;
  watchdog_params.quitting = &quitting;
  watchdog_params.connection_list = connection_list;
  watchdog_params.connection_list_sem = &connection_list_sem;
  watchdog_params.sd = sd;
  watchdog_params.sync_condition = sync_condition;
  pthread_t watchdog_thread;
  printf("creating watchdog\n");
  printf("quitting: %d; watchdog_params->quitting: %d\n", quitting ? 1 : 0, *watchdog_params.quitting ? 1 : 0);
  pthread_create(&watchdog_thread, NULL, watchdog_func, &watchdog_params);

  struct connection *connection;

  while (true) {

    // wait for input
    client_address_length = sizeof(client_address);
    message_size = recvfrom(sd, recv_buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &client_address_length);
    if (message_size == -1) {
      perror("recvfrom");
      continue;
    }

    printf("received message from address %s on port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    if (message_size <= 0) {
      continue;
    }

    char message_type = recv_buffer[0];
    switch (message_type) {
    case JOIN_GAME_ID:
      printf("received a JOIN_GAME pkt\n");

      struct connection *new_connection = malloc(sizeof(struct connection));
      if (new_connection == NULL) {
	fprintf(stderr, "out of memory, could not create new connection\n");
	continue;
      }

      memcpy(&new_connection->address, &client_address, sizeof(struct sockaddr_in));
      new_connection->in_instance = false;
      new_connection->has_left = false;
      new_connection->event = NULL_ID;

      // add to connection list
      sem_wait(&connection_list_sem);
      list_insert(connection_list, new_connection);
      sem_post(&connection_list_sem);

      send_buffer[0] = JOINED_GAME_ID;
      int bytes_sent = sendto(sd, send_buffer, 1, 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in));
      if (bytes_sent == -1) {
	printf("error sending JOINED_GAME packet\n");
      }
      break;

    case USER_INPUT_ID:
      if (message_size >= 2) {
	sem_wait(&connection_list_sem);
	connection = find_connection(&client_address, connection_list);
	if (connection != NULL) {
	  connection->event = recv_buffer[1];
	} else {
	  printf("could not find connection in USER_INPUT_ID\n");
	}
	sem_post(&connection_list_sem);
      }
      break;

    case LEAVE_GAME_ID:
      printf("received a LEAVE_GAME pkt\n");
      sem_wait(&connection_list_sem);
      connection = find_connection(&client_address, connection_list);
      if (connection != NULL) {
	connection->has_left = true;
      } else {
	printf("could not find connection in LEAVE_GAME_ID\n");
      }
      sem_post(&connection_list_sem);
      break;

    default:
      printf("received an unknown pkt\n");
      break;
    }
  }

  quitting = true;
  
  list_destroy(connection_list);

  SDL_RemoveTimer(timer_id);
  SDL_DestroyCond(sync_condition);
  SDL_Quit();

  return 0;
}

void *new_instance_func(void *_params) {
  struct new_instance_params *params = (struct new_instance_params *)_params;
  printf("in instance func\n");

  struct grid grid[params->num_players];
  int i;

  for (i = 0; i < params->num_players; i++) {
    grid_init(&grid[i], 1);
  }

  SDL_mutex *mutex = SDL_CreateMutex();
  SDL_mutexP(mutex);

  char buffer[MAX_BUFFER_SIZE];
  int row, col;

  int update_frequency = 2;
  int update_counter = 0;

  int num_disconnected = 0;

  while (num_disconnected != params->num_players) {

    if (SDL_CondWait(params->sync_condition, mutex) == -1) {
      fprintf(stderr, "SDL_CondWait: %s\n", SDL_GetError());
      continue;
    }

    num_disconnected = 0;
    for (i = 0; i < params->num_players; i++) {

      struct connection *connection = params->connections[i];

      if (connection->has_left) {
	num_disconnected++;
	continue;
      }

      if (connection->event != NULL_ID) {
	switch (connection->event) {
	case MOVE_LEFT_ID:
	  grid_move_shape_left(&grid[i]);
	  break;

	case MOVE_RIGHT_ID:
	  grid_move_shape_right(&grid[i]);
	  break;

	case MOVE_DOWN_ID:
	  grid_move_shape_down(&grid[i]);
	  break;

	case DROP_ID:
	  grid_drop_shape(&grid[i]);
	  break;

	case ROTATE_ID:
	  grid_rotate_shape(&grid[i]);
	  break;
	}
	connection->event = NULL_ID;
      }

      grid_update(&grid[i]);
    }


    if (update_counter >= update_frequency) {

      buffer[0] = GRID_UPDATE_ID;
      int index = 1;
      for (i = 0; i < params->num_players; i++) {
	for (row = 0; row < GRID_ROWS; row++) {
	  for (col = 0; col < GRID_COLUMNS; col++, index++) {
	    buffer[index] = grid_get_block_value(&grid[i], row, col);
	  }
	}
      }

      for (i = 0; i < params->num_players; i++) {
	int bytes_sent = sendto(params->sd, buffer, 401, 0, (struct sockaddr *)&params->connections[i]->address, sizeof(struct sockaddr_in));
	if (bytes_sent == -1) {
	  printf("error sending packet\n");
	}
      }

      update_counter = 0;
    } else {
      update_counter++;
    }

  }
  
  printf("exiting func\n");

  for (i = 0; i < params->num_players; i++) {
    params->connections[i]->in_instance = false;
  }
  free(params->connections);
  SDL_DestroyMutex(mutex);
  free(params);

  return 0;
}

Uint32 sync_framerate_func(Uint32 interval, void *_condition) {
  SDL_cond *condition = (SDL_cond *)_condition;
  SDL_CondBroadcast(condition);

  return interval;
}

void *watchdog_func(void *_params) {

  printf("in watchdog_func\n");
  struct watchdog_params *params = (struct watchdog_params *)_params;
  struct connection *waiting_connections[2];
  int connections_found;

  while (!(*params->quitting)) {

    connections_found = 0;
    waiting_connections[0] = NULL;
    waiting_connections[1] = NULL;

    sleep(1);

    sem_wait(params->connection_list_sem);

    struct node *connection_node = params->connection_list->first;
    while (connection_node != NULL) {
      struct connection *connection = (struct connection *)connection_node->data;

      if (!connection->has_left && !connection->in_instance) {
	waiting_connections[connections_found] = connection;
	connections_found++;
      }

      if (connections_found >= 2) {
	struct new_instance_params *instance_params = malloc(sizeof(struct new_instance_params));
	if (instance_params == NULL) {
	  fprintf(stderr, "out of memory, could not create new_instance_params\n");
	} else {

	  struct connection **connections = malloc(sizeof(struct connection *) * 2);
	  connections[0] = waiting_connections[0];
	  connections[1] = waiting_connections[1];

	  instance_params->connections = connections;
	  instance_params->sync_condition = params->sync_condition;
	  instance_params->sd = params->sd;
	  instance_params->num_players = 2;
	  connections[0]->in_instance = true;
	  connections[1]->in_instance = true;

	  pthread_t thread;
	  pthread_create(&thread, NULL, new_instance_func, instance_params);
	  printf("created new instance\n");
	}
      }
      connection_node = connection_node->next;
    }

    sem_post(params->connection_list_sem);

    printf("found %d waiting connections\n", connections_found);
  }

  printf("exiting watchdog func\n");

  return 0;
}

struct connection *find_connection(struct sockaddr_in *address, struct list *connection_list) {

  struct connection *connection;
  struct node *node = connection_list->first;
  while (node != NULL) {
    connection = (struct connection *)node->data;
    if (connection->address.sin_port == address->sin_port &&
	connection->address.sin_addr.s_addr == address->sin_addr.s_addr) {
      return connection;
    }

    node = node->next;
  }

  return NULL;
}
