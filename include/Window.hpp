#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_keyboard.h>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class Chip8;

using std::size_t;
using std::vector;

class Window {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event e;
  SDL_Texture *texture;
  size_t window_width;
  size_t window_height;
public:
  Window() {};
  Window(size_t window_width, size_t window_height, size_t texture_width,
         size_t texture_height);
  ~Window();
  bool pollRunning();
  bool check_for_key_press(int key);
  bool check_key_pressed(uint8_t key);
  uint8_t get_curr_key_pressed();
  void drawGraphics(vector<uint32_t> buffer, size_t windowWidth);
};

#endif // WINDOW_HPP