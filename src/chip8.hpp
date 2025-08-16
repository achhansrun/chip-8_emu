#ifndef CHIP_8_HPP
#define CHIP_8_HPP
#include <stdint.h>
#include <cstddef>
#include <vector>

#define STACK_SIZE 16
#define RAM_SIZE 4096

using std::size_t;
using std::vector;

class Chip8
{
public:
    static const size_t SCREEN_HEIGHT = 32;
    static const size_t SCREEN_WIDTH = 64;
    static const size_t SCREEN_SIZE = SCREEN_HEIGHT * SCREEN_WIDTH;
private:
    uint16_t program_counter;
    uint16_t index_register;
    uint8_t timer;
    uint8_t sound_timer;
    uint16_t stack[STACK_SIZE];
    uint8_t v_registers[16];
    uint8_t ram[RAM_SIZE];
    uint32_t window_buff[SCREEN_SIZE];
    vector<uint32_t> window_buffer;
    bool drawFlag = true;

public:
    Chip8();
    ~Chip8();
    bool getDrawFlag();
    void * upsizeWindowBuffer(size_t window_width, size_t window_hieght);
    vector<uint32_t> getWindowBuffer();
    size_t getWindowHeight();
    size_t getWindowWidth();
    void loadProgram();
};

#endif