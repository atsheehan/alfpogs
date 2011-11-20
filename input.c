#include "grid.h"
#include "input.h"
#include "instance.h"
#include "menu.h"
#include "net.h"

#include "SDL.h"
#include "SDL_net.h"

static void input_handle_menu_event(enum input_event event_type, struct instance *instance);
static void input_handle_game_event(enum input_event event_type, struct instance *instance);

/* Handles user input while the game is running. */
void input_handle(struct instance *instance) {

  SDL_Event event;

  /* Input events are stored in a queue until we poll for them here. Keep processing
     events until the queue is empty, and SDL_PollEvent returns 0. */
  while (SDL_PollEvent(&event)) {

    /* Since we accept input from multiple devices (keyboards and game pads), there can
       be multiple inputs that mean the same thing (left arrow on the keyboard should have
       the same effect as a left on a controller's D-pad). Here we map all of the possible
       device inputs into a subset of inputs that this game recognizes. */
    enum input_event event_type = INPUT_INVALID;

    switch (event.type) {
    case SDL_KEYDOWN:

      switch (event.key.keysym.sym) {
      case SDLK_DOWN:
	event_type = INPUT_DOWN;
	break;

      case SDLK_UP:
	event_type = INPUT_UP;
	break;

      case SDLK_LEFT:
	event_type = INPUT_LEFT;
	break;

      case SDLK_RIGHT:
	event_type = INPUT_RIGHT;
	break;

      case SDLK_SPACE:
      case SDLK_RETURN:
	event_type = INPUT_BUTTON_1;
	break;

      case SDLK_ESCAPE:
	event_type = INPUT_PAUSE;
	break;

      default:
	break;
      }
      break;

    case SDL_JOYAXISMOTION:
      if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
	printf("axis:%d, value:%d\n", event.jaxis.axis, event.jaxis.value);

	if (event.jaxis.axis == 0) {
	  if (event.jaxis.value > 0) {
	    event_type = INPUT_RIGHT;
	  }

	  if (event.jaxis.value < 0) {
	    event_type = INPUT_LEFT;
	  }
	}

	if (event.jaxis.axis == 1) {
	  if (event.jaxis.value > 0) {
	    event_type = INPUT_DOWN;
	  }

	  if (event.jaxis.value < 0) {
	    event_type = INPUT_UP;
	  }
	}
      }
      break;

    case SDL_JOYBUTTONDOWN:
	printf("button:%d\n", event.jbutton.button);
      switch (event.jbutton.button) {
      case 2:
	event_type = INPUT_BUTTON_1;
	break;

      case 9:
	event_type = INPUT_PAUSE;
      }
      break;

    case SDL_QUIT:
      event_type = INPUT_QUIT;
      break;

    default:
      break;
    }

    /* Now pass this event to another handler that is specific to the game state
       we are in. */
    if (event_type != INPUT_INVALID) {
      switch (instance->state) {
      case STATE_MENU:
	input_handle_menu_event(event_type, instance);
	break;

      case STATE_RUNNING:
	input_handle_game_event(event_type, instance);
	break;

      default:
	break;
      }
    }
  }
}

static void input_handle_menu_event(enum input_event event_type, struct instance *instance) {

  switch (event_type) {
  case INPUT_DOWN:
    menu_next_entry(&instance->menu);
    break;

  case INPUT_UP:
    menu_prev_entry(&instance->menu);
    break;

  case INPUT_QUIT:
    instance->state = STATE_QUITTING;
    break;

  case INPUT_INVALID:
    break;

  default:
    menu_handle_input(&instance->menu, instance, event_type);
    break;
  }
}

static void input_handle_game_event(enum input_event event_type, struct instance *instance) {

  switch (event_type) {
  case INPUT_DOWN:
    grid_move_shape_down(&instance->grids[instance->player_index]);
    if (instance->game_type == MULTI_PLAYER) {
      instance->net_info->packet->len = 2;
      instance->net_info->packet->data[0] = USER_INPUT_ID;
      instance->net_info->packet->data[1] = MOVE_DOWN_ID;
	  
      SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
      instance->net_info->last_time_sent = instance->net_info->time;
    }
    break;

  case INPUT_LEFT:
    grid_move_shape_left(&instance->grids[instance->player_index]);

    if (instance->game_type == MULTI_PLAYER) {
      instance->net_info->packet->len = 2;
      instance->net_info->packet->data[0] = USER_INPUT_ID;
      instance->net_info->packet->data[1] = MOVE_LEFT_ID;
	  
      SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
      instance->net_info->last_time_sent = instance->net_info->time;
    }
    break;

  case INPUT_RIGHT:
    grid_move_shape_right(&instance->grids[instance->player_index]);
    if (instance->game_type == MULTI_PLAYER) {
      instance->net_info->packet->len = 2;
      instance->net_info->packet->data[0] = USER_INPUT_ID;
      instance->net_info->packet->data[1] = MOVE_RIGHT_ID;
	  
      SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
      instance->net_info->last_time_sent = instance->net_info->time;
    }
    break;

  case INPUT_UP:
    grid_rotate_shape(&instance->grids[instance->player_index]);
    if (instance->game_type == MULTI_PLAYER) {
      instance->net_info->packet->len = 2;
      instance->net_info->packet->data[0] = USER_INPUT_ID;
      instance->net_info->packet->data[1] = ROTATE_ID;
	  
      SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
      instance->net_info->last_time_sent = instance->net_info->time;
    }
    break;

  case INPUT_BUTTON_1:
    grid_drop_shape(&instance->grids[instance->player_index]);
    if (instance->game_type == MULTI_PLAYER) {
      instance->net_info->packet->len = 2;
      instance->net_info->packet->data[0] = USER_INPUT_ID;
      instance->net_info->packet->data[1] = DROP_ID;
	  
      SDLNet_UDP_Send(instance->net_info->socket, -1, instance->net_info->packet);
      instance->net_info->last_time_sent = instance->net_info->time;
    }
    break;

  case INPUT_PAUSE:
    instance->menu.current_page = PAUSE_MENU;
    instance->state = STATE_MENU;

    if (instance->game_type == MULTI_PLAYER) {
      // send pause message?
    }
    break;

  case INPUT_QUIT:
    instance->state = STATE_QUITTING;
    if (instance->game_type == MULTI_PLAYER) {
      // send quit message
    }
    break;

  case INPUT_INVALID:
    break;

  default:
    break;

  }
}

char input_init(struct instance *instance) {
  int i;

  instance->num_controllers = SDL_NumJoysticks();
  if (instance->num_controllers > MAX_NUM_PLAYERS) {
    instance->num_controllers = MAX_NUM_PLAYERS;
  }

  fprintf(stderr, "%d controllers detected.\n", instance->num_controllers);

  if (instance->num_controllers > 0) {

    SDL_JoystickEventState(SDL_ENABLE);

    for (i = 0; i < instance->num_controllers; i++) {
      instance->controllers[i] = SDL_JoystickOpen(i);

      if (instance->controllers[i] == NULL) {
	fprintf(stderr, "Couldn't open joystick number %d.", i);
	return 0;
      }
    }
  }

  return 1;

}

void input_cleanup(struct instance *instance) {
  int i;
  
  for (i = 0; i < instance->num_controllers; i++) {
    SDL_JoystickClose(instance->controllers[i]);
  }
}
