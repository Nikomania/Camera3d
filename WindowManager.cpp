#include "WindowManager.h"
#include "WindowConstants.h"


SDL_Window* WindowManager::window = NULL;
SDL_Renderer* WindowManager::renderer = NULL;
Uint64 WindowManager::last_time = 0;

bool WindowManager::Setup() {
    SDL_SetAppMetadata("Example Renderer Points", "1.0", "com.example.renderer-points");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (
        !SDL_CreateWindowAndRenderer(
            "examples/renderer/points",
            WindowConstants::WINDOW_WIDTH,
            WindowConstants::WINDOW_HEIGHT,
            SDL_WINDOW_RESIZABLE,
            &window,
            &renderer
        )
    ) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderLogicalPresentation(
        renderer,
        WindowConstants::WINDOW_WIDTH,
        WindowConstants::WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

	UpdateLastTime();

    return true;
}

void WindowManager::RenderPoints(SDL_FPoint* points, size_t total_points) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(renderer, points, total_points);

    SDL_RenderPresent(renderer);
}
