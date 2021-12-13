#include <SDL.h>
#include "simple_logger.h"
#include "timer.h"

float deltaTime = 0;

Timer* timer_assign(Timer* timer) {
    if (!timer) {
      slog("failed to load timer in assign");
      return;
    }
    timer->currentTime = 0;
    timer->deltaTime = 0;
    timer->frameCount = 0;
    timer->prevTime = 0;
    return timer;
}

void timer_update(Timer* timer) {
    if (!timer) return;
    timer->prevTime = timer->currentTime;
    timer->currentTime = SDL_GetTicks();
    timer->deltaTime = (timer->currentTime - timer->prevTime) / 1000.0f;
    deltaTime = timer->deltaTime;
    timer->frameCount += timer->deltaTime;
}
float get_DeltaTime() {
    return deltaTime;
}
