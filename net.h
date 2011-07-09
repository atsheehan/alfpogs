#ifndef NET_H
#define NET_H

#include "SDL_net.h"
#include <stdbool.h>

#define PACKET_BUFFER_SIZE 1000

#define JOIN_GAME_ID	1
#define LEAVE_GAME_ID	2
#define GRID_UPDATE_ID	3
#define USER_INPUT_ID	4
#define GAME_FULL_ID 5
#define JOINED_GAME_ID 6

enum net_state {
  INIT,
  JOIN_SENT,
  JOIN_DENY,
  WAIT_START,
  RUNNING,
  GAME_OVER
};

struct net_info {
  int port;
  UDPsocket socket;
  UDPpacket *packet;

  enum net_state state;
  unsigned int last_time_sent;
  unsigned int last_time_received;
  unsigned int time;
};

enum input_event {
  NULL_ID = 0,
  MOVE_LEFT_ID = 1,
  MOVE_RIGHT_ID = 2,
  MOVE_DOWN_ID = 3,
  DROP_ID = 4,
  ROTATE_ID = 5
};

bool net_init(struct net_info *net_info, const char *hostname, int port);
void net_destroy(struct net_info *net_info);

#endif /* NET_H */

