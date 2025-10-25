# Chip 8 Emulator

[![Lint](https://github.com/achhansrun/chip-8_emu/actions/workflows/lint.yml/badge.svg)](https://github.com/achhansrun/chip-8_emu/actions/workflows/lint.yml)  
Creating a chip-8 emulator in c++

## How to start contributing

First clone the repo:  
`git clone https://github.com/achhansrun/chip-8_emu.git`  
Next, fetch submodules:  
`git submodule update --init --recursive`

### How to build

First this command to configure debug build:  
`cmake -DCMAKE_BUILD_TYPE=Debug . -B build/`  
or this command to configure release build:  
`cmake -DCMAKE_BUILD_TYPE=Release . -B build/`
Next this command to finally build all types:  
`cmake --build build`
