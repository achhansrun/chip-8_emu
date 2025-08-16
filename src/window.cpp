#include "window.hpp"
#include <iostream>


Window::Window(size_t window_width, size_t window_height, size_t texture_width, size_t texture_height) : window_height(window_height), window_width(window_width) {
    SDL_Init(SDL_INIT_VIDEO);
    Window::window = SDL_CreateWindow("Hello, Triangle!", window_width, window_height, SDL_WINDOW_RESIZABLE);
    if (Window::window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(Window::window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(Window::window);
        SDL_Quit();
    }
    texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
    texture_width, texture_height);
    if (texture == nullptr)
    {
        std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(Window::window);
        SDL_DestroyRenderer(Window::renderer);
        SDL_Quit();
    }
}

void Window::drawGraphics(vector<uint32_t> buffer, size_t windowWidth) {
    // Update texture with buffer 
    SDL_UpdateTexture(Window::texture, nullptr, buffer.data(), windowWidth * sizeof(uint32_t));
    // Clear screen
    SDL_RenderClear(Window::renderer);
    // Render the updated texture
    SDL_RenderTexture(Window::renderer, Window::texture, nullptr, nullptr);

    SDL_RenderPresent(Window::renderer);
}

bool Window::pollRunning() {
    SDL_PollEvent(&e);
    if (e.type == SDL_EVENT_QUIT)
    {
        return false;
    }
    return true;
}

Window::~Window() {
    SDL_DestroyTexture(texture);
    // Destroy the renderer
    SDL_DestroyRenderer(renderer);
    // destroy the window
    SDL_DestroyWindow(window);
    // Quit sdl
    SDL_Quit();
}
