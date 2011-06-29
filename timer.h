#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include "SDL_thread.h"

#define FRAMES_PER_SECOND 30

bool timer_init(void);
void timer_cleanup(void);

void timer_wait_for_next_frame(SDL_mutex *locked_mutex);

#endif // TIMER_H
