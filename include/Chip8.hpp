#ifndef CHIP_8_HPP
#define CHIP_8_HPP

#include <cstddef>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>
#include "Timer.hpp"
// For Timer object
#include "Window.hpp"

using std::size_t;
using std::vector;

class Chip8 {
public:
  static const size_t SCREEN_HEIGHT = 32;
  static const size_t SCREEN_WIDTH = 64;
  static const size_t SCREEN_SIZE = SCREEN_HEIGHT * SCREEN_WIDTH;
  static const size_t NUM_KEYS = 16;
  Timer timer;
  SoundTimer sound_timer;
  bool getDrawFlag();
  void setDrawFlag(bool flag);
  vector<uint32_t> getWindowBuffer();
  size_t getWindowHeight();
  size_t getWindowWidth();
  void loadProgram(const std::string &program);
  void emulateCycle();
  Window window;
  Chip8() {};
  Chip8(const Window & window);
  ~Chip8();
private:
  static const size_t STACK_SIZE = 16;
  static const size_t RAM_SIZE = 4096;
  static const size_t NUM_VREGS = 16;
  static const size_t FONT_LOCATION = 0x50;
  uint16_t program_counter;
  uint16_t index_register;
  std::stack<uint16_t> stack;
  uint8_t v_registers_buffer[NUM_VREGS];
  vector<uint8_t> v_registers;
  uint8_t ram_buffer[RAM_SIZE];
  uint32_t window_buff[SCREEN_SIZE];
  vector<uint8_t> ram;
  vector<uint32_t> window_buffer;
  bool drawFlag = true;
  uint16_t current_instruction;
  void fetchInstruction();
  void decodeInstruction();
  void clearScreen();
  void returnFromSubroutine();
  void call(uint16_t addr);
  void jump(uint16_t addr);
  void draw(uint8_t x, uint8_t y, uint8_t height);
  uint8_t get_key();
  uint8_t key();
};

#endif