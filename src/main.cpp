#include "Chip8.hpp"
#include "Window.hpp"
#include <iostream>
#include <string>
#include <thread>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 320

int main(int argc, char const *argv[]) {
  float timing_hertz;
  switch (argc) {
  case 3:
    timing_hertz = SDL_atoi(argv[2]);
    break;
  case 2:
    std::cerr << "chip8: timing not provided! Using 60 hertz\n";
    std::cerr << "usage: chip8 <input_file> [timing in hertz]\n";
    timing_hertz = 500;
    break;
  case 1:
    std::cerr << "chip8: ERROR: not enough arguments!\n";
    std::cerr << "usage: chip8 <input_file> [timing in hertz]\n";
    return EXIT_FAILURE;
  default:
    std::cerr << "chip8: ignoring extra inputs!\n";
    std::cerr << "usage: chip8 <input_file> [timing in hertz]\n";
    timing_hertz = SDL_atof(argv[2]);
    break;
  }

  Window win = Window(WINDOW_HEIGHT, WINDOW_WIDTH, Chip8::SCREEN_WIDTH,
                      Chip8::SCREEN_HEIGHT);
  Chip8 chip8 = Chip8(win);

  std::thread timer_thread(&Timer::update_timer, &chip8.timer);

  std::string programFile = std::string(argv[1]);
  
  chip8.loadProgram(programFile);
  
  while (win.pollRunning()) {
    // sleep to emulate slower tick rate of chip8
    chip8.emulateCycle();
    if (chip8.getDrawFlag()) {
      win.drawGraphics(chip8.getWindowBuffer(), chip8.getWindowWidth());
      chip8.setDrawFlag(false);
    }
    // Ensure that the program is running at the right timing
    SDL_Delay((uint32_t)((1/(float)timing_hertz)*1000));
  }
  return 0;
}
