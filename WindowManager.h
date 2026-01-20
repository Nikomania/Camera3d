#pragma once

#include <SDL3/SDL.h>


class WindowManager {
public:
    WindowManager() = default;
    ~WindowManager() = default;
    
    bool Setup();
    void RenderPoints(SDL_FPoint* points, size_t total_points);

    inline void UpdateLastTime() {
        last_time = SDL_GetTicks();
	}
    inline Uint64 GetLastTime() const {
        return last_time;
	}
private:
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static Uint64 last_time;
};
