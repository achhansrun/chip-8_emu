#include <iostream>
#include "window.hpp"
#include "chip8.hpp"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 320

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    Window win = Window(WINDOW_HEIGHT, WINDOW_WIDTH);
    Chip8 chip8 = Chip8();
    while (win.pollRunning()) {
        if (chip8.getDrawFlag()) {  
            // uint32_t *upscaled_window_buffer = (uint32_t *)chip8.upsizeWindowBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);    
            win.drawGraphics(chip8.getWindowBuffer(), sizeof(chip8.getWindowBuffer()));
            // delete[] upscaled_window_buffer;
        }
    }

    return 0;
}
