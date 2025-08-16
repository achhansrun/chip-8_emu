#include "chip8.hpp"


Chip8::Chip8() {
    window_buffer = vector<uint32_t>(window_buff, window_buff+SCREEN_SIZE);
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            window_buffer[y * SCREEN_WIDTH + x] = 0; // -1 = 0xFFFFFFF ARGB
        }
    }
    
}

bool Chip8::getDrawFlag() {
    return drawFlag;
}

// Need to free memory after calling
void * Chip8::upsizeWindowBuffer(size_t window_width, size_t window_height) {
    uint32_t *new_buffer = new uint32_t(window_width * window_height);
    size_t upscale_size_width = window_width / SCREEN_WIDTH;
    size_t upscale_size_height = window_height / SCREEN_HEIGHT;

    size_t adjustment_for_upscaled_section_x = 0; 
    size_t adjustment_for_upscaled_section_y = 0;
    for (size_t y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (size_t x = 0; x < SCREEN_WIDTH; x++)
        {
            for (size_t i = 0; i < upscale_size_height; i++)
            {
                for (size_t j = 0; j < upscale_size_width; j++)
                {
                    new_buffer[(y*SCREEN_HEIGHT + i)+(x+j)] = window_buffer[y * SCREEN_WIDTH + x];
                    
                }
                
            }
        }
        adjustment_for_upscaled_section_y += upscale_size_height-1;
    }
    return new_buffer;
}

vector<uint32_t> Chip8::getWindowBuffer() {
    return window_buffer;
}

size_t Chip8::getWindowHeight() {
    return SCREEN_HEIGHT;
}

size_t Chip8::getWindowWidth() {
    return SCREEN_WIDTH;
}

void Chip8::loadProgram() {

}

Chip8::~Chip8() {

}