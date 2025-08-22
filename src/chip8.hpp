#ifndef CHIP_8_HPP
#define CHIP_8_HPP
#include <stdint.h>
#include <cstddef>
#include <vector>
#include <string>

using std::size_t;
using std::vector;

class Chip8
{
public:
    static const size_t SCREEN_HEIGHT = 32;
    static const size_t SCREEN_WIDTH = 64;
    static const size_t SCREEN_SIZE = SCREEN_HEIGHT * SCREEN_WIDTH;
private:
    static const size_t STACK_SIZE = 16;
    static const size_t RAM_SIZE = 4096;
    static const size_t NUM_VREGS = 16;
    static const size_t FONT_LOCATION = 0x50;
    uint16_t program_counter;
    uint16_t index_register;
    uint8_t timer;
    uint8_t sound_timer;
    uint16_t stack_buff[STACK_SIZE];
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
public:
    Chip8();
    ~Chip8();
    bool getDrawFlag();
    void setDrawFlag(bool flag);
    vector<uint32_t> getWindowBuffer();
    size_t getWindowHeight();
    size_t getWindowWidth();
    void loadProgram(const std::string &program);
    void emulateCycle();
};

#endif