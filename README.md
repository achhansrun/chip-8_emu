# Chip 8 Emulator

[![Super-Lint](https://github.com/achhansrun/chip-8_emu/actions/workflows/super-lint.yml/badge.svg)](https://github.com/achhansrun/chip-8_emu/actions/workflows/super-lint.yml)
Creating a chip-8 emulator in c++

## How to start contributing

First clone the repo:  
`git clone https://github.com/achhansrun/chip-8_emu.git`  
Next, fetch submodules:  
`git submodule update --init --recursive`

### How to do debug build

First this command to configure build:  
`cmake -S . -B build/Debug`  
Next this command to finally build:  
`cmake --build build/Debug`
