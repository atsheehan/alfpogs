#ifndef INPUT_H
#define INPUT_H

#include "instance.h"

enum input_event {
  INPUT_INVALID,
  INPUT_UP,
  INPUT_DOWN,
  INPUT_LEFT,
  INPUT_RIGHT,
  INPUT_BUTTON_1,
  INPUT_BUTTON_2,
  INPUT_PAUSE,
  INPUT_QUIT
};

char input_init(struct instance *instance);
void input_handle(struct instance *instance);
void input_cleanup(struct instance *instance);

#endif /* INPUT_H */
