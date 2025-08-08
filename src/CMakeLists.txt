# Glob all source from src to feed into add_executable
file(GLOB helloworld_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
# Create your game executable target as usual
add_executable(hello WIN32 ${helloworld_SRC})