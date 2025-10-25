cmake_minimum_required(VERSION 3.16)
project(chip8)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


# This assumes the SDL source is available in vendored/SDL
add_subdirectory(./vendored/SDL EXCLUDE_FROM_ALL)

# Project source directory
# Glob all source from src to feed into add_executable
file(GLOB chip8_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# Create your executable target as usual
add_executable(chip8 WIN32 ${chip8_SRC})
target_include_directories(chip8 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Link to the actual SDL3 library.
target_link_libraries(chip8 PRIVATE SDL3::SDL3)