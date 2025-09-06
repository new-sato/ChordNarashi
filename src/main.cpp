#include "allClassManager.hpp"
#include <SDL2/SDL.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    allClassManager a;
    a.mainLoop();
    return 0;
}