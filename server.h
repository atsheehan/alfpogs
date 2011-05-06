#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <stdbool.h>

#define PORT 4485
#define BUFFER_SIZE 1024

bool server_init(void);
void server_cleanup(void);
int server_run_multiplayer_game(void *_details);

#endif /* GAME_SERVER_H */
