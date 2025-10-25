#include "Chip8.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

uint8_t fontset[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
  // Set program counter to 0x200 for initialization
  this->program_counter = 0x200;
  // Initialize registers
  this->v_registers = vector<uint8_t>(
      this->v_registers_buffer, this->v_registers_buffer + this->NUM_VREGS);
  // Zero out registers
  std::fill(this->v_registers.begin(), this->v_registers.end(), 0);
  // Initialize ram
  this->ram = vector<uint8_t>(ram_buffer, ram_buffer + this->RAM_SIZE);
  // Zero out memory
  std::fill(this->ram.begin(), this->ram.end(), 0);
  this->window_buffer =
      vector<uint32_t>(window_buff, window_buff + this->SCREEN_SIZE);
  this->clearScreen();

  // Load memory with fontset
  for (size_t i = 0; i < sizeof(fontset); i++) {
    ram[0x50 + i] = fontset[i];
  }
  // Reset timers
}

bool Chip8::getDrawFlag() { return this->drawFlag; }

vector<uint32_t> Chip8::getWindowBuffer() { return this->window_buffer; }

size_t Chip8::getWindowHeight() { return this->SCREEN_HEIGHT; }

size_t Chip8::getWindowWidth() { return this->SCREEN_WIDTH; }

void Chip8::clearScreen() {
  // clear window buffer
  std::fill(this->window_buffer.begin(), this->window_buffer.end(), 0);
}

void Chip8::loadProgram(const std::string &program) {
  std::streampos size;
  try {
    std::ifstream program_file(program,
                               std::ios::in | std::ios::binary | std::ios::ate);
    size = program_file.tellg();
    std::cout << program_file.is_open() << std::endl;
    program_file.seekg(0, std::ios::beg);
    char *buffer = new char[size];
    program_file.read(buffer, size);
    for (size_t i = 0; i < size; i++) {
      ram[i + 0x200] = buffer[i];
    }
    delete[] buffer;
    program_file.close();
    std::cout << "Loaded program: " << program << " into chip 8 ram."
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}

void Chip8::fetchInstruction() {
  this->current_instruction = (this->ram[this->program_counter] & 0xFF) << 8 |
                              (this->ram[this->program_counter + 1] & 0xff);
  std::cout << "Fetched instruction: " << std::hex << this->current_instruction
            << std::endl;
  this->program_counter += 2;
}

void Chip8::returnFromSubroutine() {
  this->program_counter = this->stack.top();
  this->stack.pop();
}

void Chip8::call(uint16_t addr) {
  this->stack.push(this->program_counter);
  this->jump(addr);
}

void Chip8::jump(uint16_t addr) { this->program_counter = addr; }

void Chip8::draw(uint8_t x, uint8_t y, uint8_t height) {
  this->v_registers[0xf] = 0;
  // Go through the height of the sprite, grab the byte associated, and render
  // each of those pixels coresponding to the bits of that byte
  for (size_t i = 0; i < height; i++) {
    uint8_t sprite_byte = this->ram[this->index_register + i];
    // Go through each bit in the sprite's byte
    if ((y + i) > SCREEN_HEIGHT) {
      break;
    }

    for (size_t j = 0; j < 8; j++) {
      uint8_t bitI = (sprite_byte >> (7 - j)) & 1
      if (x + j > SCREEN_WIDTH) {
        continue;
      }
      // XOR the pixel at the bit t
      if ((this->window_buffer[(x + j) + (SCREEN_WIDTH * (y + i))] == -1) &&
          (bitI == 1)) {
        this->window_buffer[(x + j) + (SCREEN_WIDTH * (y + i))] = 0;
        this->v_registers[0xf] = 1;
      } else if (bitI == 0) {
        continue;
      } else {
        this->window_buffer[(x + j) + (SCREEN_WIDTH * (y + i))] = -1;
      }
    }
  }
  this->drawFlag = true;
}

uint8_t get_first_nibble(uint16_t instruction) {
  return (instruction & 0xf000) >> 12;
}

uint8_t get_second_nibble(uint16_t instruction) {
  return (instruction & 0x0f00) >> 8;
}

uint8_t get_third_nibble(uint16_t instruction) {
  return (instruction & 0x00f0) >> 4;
}

uint8_t get_fourth_nibble(uint16_t instruction) {
  return (instruction & 0x000f) >> 0;
}

uint16_t get_NNN(uint16_t instruction) { return (instruction & 0x0fff); }

uint8_t get_NN(uint16_t instruction) { return (instruction & 0x00ff); }

void Chip8::decodeInstruction() {
  uint8_t nibble_one = get_first_nibble(this->current_instruction);
  uint8_t nibble_two = get_second_nibble(this->current_instruction);
  uint8_t nibble_three = get_third_nibble(this->current_instruction);
  uint8_t nibble_four = get_fourth_nibble(this->current_instruction);
  uint16_t NNN = get_NNN(this->current_instruction);
  uint8_t NN = get_NN(this->current_instruction);
  switch (nibble_one) {
  case 0x0:
    if (this->current_instruction == 0x00E0) {
      this->clearScreen();
      this->drawFlag = true;
    } else if (this->current_instruction == 0x00EE) {
      this->returnFromSubroutine();
    } else {
      this->call(NNN);
    }
    break;
  case 0x1:
    this->jump(NNN);
    break;
  case 0x2:
    this->call(NNN);
    break;
  case 0x3:
    if (v_registers[nibble_two] == NN) {
      this->program_counter += 2;
    }
    break;
  case 0x4:
    if (v_registers[nibble_two] != NN) {
      this->program_counter += 2;
    }
    break;
  case 0x5:
    if (v_registers[nibble_two] == v_registers[nibble_three]) {
      this->program_counter += 2;
    }
    break;
  case 0x6:
    v_registers[nibble_two] = NN;
    break;
  case 0x7:
    v_registers[nibble_two] += NN;
    break;
  case 0xa:
    this->index_register = NNN;
    break;
  case 0xc:
    v_registers[nibble_two] = rand() & NN;
    break;
  case 0xd:
    this->draw(v_registers[nibble_two] % 64, v_registers[nibble_three] % 32,
               nibble_four);
    break;
  case 0xf:
    switch (NN) {
    case 0x07:
      // TODO:
      // Vx = get_delay()
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x0A:
      // TODO:
      // Vx = get_key()
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x15:
      // TODO:
      // delay_timer(Vx)
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x18:
      // TODO:
      // sound_timer(Vx)
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x1E:
      this->index_register += v_registers[nibble_two];
      break;
    case 0x29:
      index_register = 0x50 + (v_registers[nibble_two] * 5);
      break;
    case 0x33:
      // TODO:
      // set_BCD(Vx)
      // *(I+0) = BCD(3);
      // *(I+1) = BCD(2);
      // *(I+2) = BCD(1);
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x55:
      // TODO:
      // reg_dump(Vx, &I)
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    case 0x65:
      // TODO:
      // reg_load(Vx, &I)
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    default:
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;
    }
    break;
  case 0xe:
    switch (NN) {
    case 0x69:
      std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
                << this->current_instruction << std::endl;
      break;

    default:
      break;
    }
  default:
    std::cout << "ERROR INSTRUCTION NOT IMPLEMENTED: " << std::hex
              << this->current_instruction << std::endl;
    break;
  }
}

void Chip8::emulateCycle() {
  this->fetchInstruction();
  this->decodeInstruction();
}

void Chip8::setDrawFlag(bool flag) { this->drawFlag = flag; }

Chip8::~Chip8() {}