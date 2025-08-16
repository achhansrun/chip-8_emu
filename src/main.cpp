#include <iostream>
#include "window.hpp"
#include "chip8.hpp"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 320

int main(int argc, char const *argv[]) {
    Window win = Window(WINDOW_HEIGHT, WINDOW_WIDTH, Chip8::SCREEN_WIDTH, Chip8::SCREEN_HEIGHT);
    Chip8 chip8 = Chip8();
    while (win.pollRunning()) {
        if (chip8.getDrawFlag()) {  
            win.drawGraphics(chip8.getWindowBuffer(), chip8.getWindowWidth());
        }
    }
    return 0;
}
