#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "WindowConstants.h"
#include "WindowManager.h"

#define NUM_POINTS 500
#define MIN_PIXELS_PER_SECOND 30  /* move at least this many pixels per second. */
#define MAX_PIXELS_PER_SECOND 60  /* move this many pixels per second at most. */


WindowManager windowManager;

/* (track everything as parallel arrays instead of a array of structs,
   so we can pass the coordinates to the renderer in a single function call.) */

   /* Points are plotted as a set of X and Y coordinates.
      (0, 0) is the top left of the window, and larger numbers go down
      and to the right. This isn't how geometry works, but this is pretty
      standard in 2D graphics. */
static SDL_FPoint points[NUM_POINTS];
static float point_speeds[NUM_POINTS];

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    int i;

    if (!windowManager.Setup()) {
        return SDL_APP_FAILURE;
	}

    /* set up the data for a bunch of points. */
    for (i = 0; i < SDL_arraysize(points); i++) {
        points[i].x = SDL_randf() * ((float)WindowConstants::WINDOW_WIDTH);
        points[i].y = SDL_randf() * ((float)WindowConstants::WINDOW_HEIGHT);
        point_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    const Uint64 now = SDL_GetTicks();
    const float elapsed = ((float)(now - windowManager.GetLastTime())) / 1000.0f;  /* seconds since last iteration */
    int i;

    /* let's move all our points a little for a new frame. */
    for (i = 0; i < SDL_arraysize(points); i++) {
        const float distance = elapsed * point_speeds[i];
        points[i].x += distance;
        points[i].y += distance;
        if ((points[i].x >= WindowConstants::WINDOW_WIDTH) || (points[i].y >= WindowConstants::WINDOW_HEIGHT)) {
            /* off the screen; restart it elsewhere! */
            if (SDL_rand(2)) {
                points[i].x = SDL_randf() * ((float)WindowConstants::WINDOW_WIDTH);
                points[i].y = 0.0f;
            }
            else {
                points[i].x = 0.0f;
                points[i].y = SDL_randf() * ((float)WindowConstants::WINDOW_HEIGHT);
            }
            point_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
        }
    }

    windowManager.UpdateLastTime();
	windowManager.RenderPoints(points, NUM_POINTS);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
}
