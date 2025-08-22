#include <iostream>
#include "window.hpp"
#include "chip8.hpp"
#include <string>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 320

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cerr << "chip8: missing input file!\n";
        std::cerr << "usage: chip8 <input_file>\n";
        return EXIT_FAILURE;
    }
    Window win = Window(WINDOW_HEIGHT, WINDOW_WIDTH, Chip8::SCREEN_WIDTH, Chip8::SCREEN_HEIGHT);
    Chip8 chip8 = Chip8();
    std::string programFile = std::string(argv[1]);
    chip8.loadProgram(programFile);

    while (win.pollRunning()) {
        //sleep to emulate slower tick rate of chip8
        chip8.emulateCycle();
        if (chip8.getDrawFlag()) {  
            win.drawGraphics(chip8.getWindowBuffer(), chip8.getWindowWidth());
            chip8.setDrawFlag(false);
        }
    }
    return 0;
}
