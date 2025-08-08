#include "window.hpp"

void Window::renderClear() {
    SDL_RenderClear(renderer);
}

Window::Window() {
    SDL_Init(SDL_INIT_VIDEO);
    Window::window = SDL_CreateWindow("Hello, Triangle!", 960, 540, SDL_WINDOW_RESIZABLE);
    if (Window::window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(Window::window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(Window::window);
        SDL_Quit();
    }

}

void Window::drawGraphics() {
    // TODO:
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
    // Destroy the renderer
    SDL_DestroyRenderer(renderer);
    // destroy the window
    SDL_DestroyWindow(window);
    // Quit sdl
    SDL_Quit();
}
