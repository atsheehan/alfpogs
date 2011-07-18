#include "input.h"
#include "SDL.h"
#include "instance.h"
#include "grid.h"
#include "net.h"
#include "menu.h"
#include "SDL_net.h"

/* Handles user input while the game is running. */
void input_handle(struct instance *instance) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {

    switch (instance->state) {

    case STATE_MENU:
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_DOWN:
	  menu_next_entry(&instance->menu);
	  break;

	case SDLK_UP:
	  menu_prev_entry(&instance->menu);
	  break;

	default:
	  break;
	}
	break;

      case SDL_QUIT:
	instance->state = STATE_QUITTING;
	break;
      }
      break;
      

    case STATE_RUNNING:

      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_LEFT:
	  grid_move_shape_left(&instance->grids[instance->player_index]);

	  if (instance->game_type == MULTI_PLAYER) {
	    instance->net_info->packet->len = 2;
	    instance->net_info->packet->data[0] = USER_INPUT_ID;
	    instance->net_info->packet->data[1] = MOVE_LEFT_ID;
	  
	    SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
	    instance->net_info->last_time_sent = instance->net_info->time;
	  }
	  break;
	case SDLK_RIGHT:
	  grid_move_shape_right(&instance->grids[instance->player_index]);
	  if (instance->game_type == MULTI_PLAYER) {
	    instance->net_info->packet->len = 2;
	    instance->net_info->packet->data[0] = USER_INPUT_ID;
	    instance->net_info->packet->data[1] = MOVE_RIGHT_ID;
	  
	    SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
	    instance->net_info->last_time_sent = instance->net_info->time;
	  }
	  break;
	case SDLK_DOWN:
	  grid_move_shape_down(&instance->grids[instance->player_index]);
	  if (instance->game_type == MULTI_PLAYER) {
	    instance->net_info->packet->len = 2;
	    instance->net_info->packet->data[0] = USER_INPUT_ID;
	    instance->net_info->packet->data[1] = MOVE_DOWN_ID;
	  
	    SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
	    instance->net_info->last_time_sent = instance->net_info->time;
	  }
	  break;
	case SDLK_SPACE:
	  grid_rotate_shape(&instance->grids[instance->player_index]);
	  if (instance->game_type == MULTI_PLAYER) {
	    instance->net_info->packet->len = 2;
	    instance->net_info->packet->data[0] = USER_INPUT_ID;
	    instance->net_info->packet->data[1] = ROTATE_ID;
	  
	    SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
	    instance->net_info->last_time_sent = instance->net_info->time;
	  }
	  break;
	case SDLK_UP:
	  grid_drop_shape(&instance->grids[instance->player_index]);
	  if (instance->game_type == MULTI_PLAYER) {
	    instance->net_info->packet->len = 2;
	    instance->net_info->packet->data[0] = USER_INPUT_ID;
	    instance->net_info->packet->data[1] = DROP_ID;
	  
	    SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
	    instance->net_info->last_time_sent = instance->net_info->time;
	  }
	  break;
	case SDLK_ESCAPE:
	  instance->state = STATE_QUITTING;
	  if (instance->game_type == MULTI_PLAYER) {
	    // send quit message
	  }
	default:
	  break;
	}
	break;

      case SDL_QUIT:
	instance->state = STATE_QUITTING;
	if (instance->game_type == MULTI_PLAYER) {
	  // send quit message
	}
	break;
      }
      break;

    default:
      break;
    }
  }
}
