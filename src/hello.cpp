#include <iostream>
#include "window.hpp"

int main(int argc, char const *argv[])
{
    Window win = Window();

    while (win.pollRunning()) {
        win.renderClear();
    }
    return 0;
}
