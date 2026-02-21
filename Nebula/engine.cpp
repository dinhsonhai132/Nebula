#include "engine.hpp"

bool Engine::init(int w, int h, char* title) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return false;

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        0
    );

    if (!window)
        return false;

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
        return false;

    running = true;
    return true;
}

void Engine::poll_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Engine::clear(float r, float g, float b) {
    SDL_SetRenderDrawColor(
        renderer,
        (Uint8)(r * 255),
        (Uint8)(g * 255),
        (Uint8)(b * 255),
        255
    );
    SDL_RenderClear(renderer);
}

void Engine::present() {
    SDL_RenderPresent(renderer);
}

bool Engine::is_running() const {
    return running;
}

void Engine::shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::draw_rect(float x, float y, float w, float h, int r, int g, int b) {

    SDL_Rect rect;
    rect.x = (int)x;
    rect.y = (int)y;
    rect.w = (int)w;
    rect.h = (int)h;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Engine::key_down(SDL_Scancode key) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[key];
}