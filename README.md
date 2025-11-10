# Chip 8 Emulator

[![Lint](https://github.com/achhansrun/chip-8_emu/actions/workflows/lint.yml/badge.svg)](https://github.com/achhansrun/chip-8_emu/actions/workflows/lint.yml)  
Creating a chip-8 emulator in c++

## How to start contributing

First clone the repo:  
`git clone https://github.com/achhansrun/chip-8_emu.git`  
Next, fetch submodules:  
`git submodule update --init --recursive`

### How to build

Install dependencies:  
`sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev`

First this command to configure debug build:  
`cmake -DCMAKE_BUILD_TYPE=Debug . -B build/`  
or this command to configure release build:  
`cmake -DCMAKE_BUILD_TYPE=Release . -B build/`  
Next this command to finally build all types:  
`cmake --build build`
