#include "Window.hpp"
#include <iostream>
#include "Chip8.hpp"

Window::Window(size_t window_width, size_t window_height, size_t texture_width,
               size_t texture_height)
    : window_height(window_height), window_width(window_width) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  Window::window = SDL_CreateWindow("Chip-8 Emu", window_width, window_height,
                                    SDL_WINDOW_RESIZABLE | 
                                    SDL_WINDOW_INPUT_FOCUS |
                                    SDL_WINDOW_ALWAYS_ON_TOP | 
                                    SDL_WINDOW_MOUSE_FOCUS
                                    );
  if (Window::window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
  }
  renderer = SDL_CreateRenderer(Window::window, NULL);
  if (renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(Window::window);
    SDL_Quit();
  }
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, texture_width,
                              texture_height);
  if (texture == nullptr) {
    std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(Window::window);
    SDL_DestroyRenderer(Window::renderer);
    SDL_Quit();
  }
}

void Window::drawGraphics(vector<uint32_t> buffer, size_t windowWidth) {
  // Update texture with buffer
  SDL_UpdateTexture(Window::texture, nullptr, buffer.data(),
                    windowWidth * sizeof(uint32_t));
  // Clear screen
  SDL_RenderClear(Window::renderer);
  // Render the updated texture
  SDL_RenderTexture(Window::renderer, Window::texture, nullptr, nullptr);

  SDL_RenderPresent(Window::renderer);
}

bool Window::pollRunning() {
  SDL_PollEvent(&e);
  if (e.type == SDL_EVENT_QUIT) {
    return false;
  }
  return true;
}

bool Window::check_key_pressed(uint8_t key) {
    SDL_PollEvent(&e);
    SDL_PumpEvents();
    const bool *keyboard_state = SDL_GetKeyboardState(NULL);

    switch (key)
    {
    case 0:
      return keyboard_state[SDL_SCANCODE_Z];
      break;
    case 1:
      return keyboard_state[SDL_SCANCODE_X];
      break;
    case 2:
      return keyboard_state[SDL_SCANCODE_C];
      break;
    case 3:
      return keyboard_state[SDL_SCANCODE_V];
      break;
    case 4:
      return keyboard_state[SDL_SCANCODE_A];
      break;
    case 5:
      return keyboard_state[SDL_SCANCODE_S];
      break;
    case 6:
      return keyboard_state[SDL_SCANCODE_D];
      break;
    case 7:
      return keyboard_state[SDL_SCANCODE_F];
      break;
    case 8:
      return keyboard_state[SDL_SCANCODE_Q];
      break;
    case 9:
      return keyboard_state[SDL_SCANCODE_W];
      break;
    case 0xa:
      return keyboard_state[SDL_SCANCODE_E];
      break;
    case 0xb:
      return keyboard_state[SDL_SCANCODE_R];
      break;
    case 0xc:
      return keyboard_state[SDL_SCANCODE_1];
      break;
    case 0xd:
      return keyboard_state[SDL_SCANCODE_2];
      break;
    case 0xe:
      return keyboard_state[SDL_SCANCODE_3];
      break;
    case 0xf:
      return keyboard_state[SDL_SCANCODE_4];
      break;
    }
  return false;
}

uint8_t Window::get_curr_key_pressed() {
  SDL_Event event;
  while(this->window != SDL_GetKeyboardFocus())
  {}
  for (size_t i = 0; i < Chip8::NUM_KEYS; i++)
  {
    if(check_key_pressed(i)) {
      std::cout << "Pressed: " << i << " key" << std::endl;
      return i;
    }
    
  }
  return Chip8::NUM_KEYS+1;
}

bool Window::check_for_key_press(int key) {
  SDL_Event event;
  if (this->window != SDL_GetKeyboardFocus())
  {
    return false;
  }
  return check_key_pressed(key);
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
