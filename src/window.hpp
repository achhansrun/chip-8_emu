#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <stdexcept>

class Window {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
public:
    Window();
    ~Window();
    bool pollRunning();
    void renderClear();
    void drawGraphics();
};

#endif // WINDOW_HPP