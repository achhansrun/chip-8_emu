# Glob all source from src to feed into add_executable
file(GLOB chip8_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
# Create your game executable target as usual
add_executable(chip8 WIN32 ${chip8_SRC})