#pragma once
#include <SDL2/SDL.h>

class Engine {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = false;

public:
    bool init(int w, int h, char* title);
    void poll_events();
    void clear(float r, float g, float b);
    void present();
    bool is_running() const;
    void draw_rect(float x, float y, float w, float h, int r, int g, int b);
    bool key_down(SDL_Scancode key);

    SDL_Renderer* get_renderer() { return renderer; }

    void shutdown();
};
