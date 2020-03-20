#include "timer.h"

Uint32 Timer::getTime() {
  return SDL_GetTicks();
}
