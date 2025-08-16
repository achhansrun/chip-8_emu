#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <vector>

using std::vector;
using std::size_t;

class Window {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    SDL_Texture* texture;
    size_t window_width;
    size_t window_height;
public:
    Window(size_t window_width, size_t window_height, size_t texture_width, size_t texture_height);
    ~Window();
    bool pollRunning();
    void drawGraphics(vector<uint32_t> buffer, size_t windowWidth);
};

#endif // WINDOW_HPP