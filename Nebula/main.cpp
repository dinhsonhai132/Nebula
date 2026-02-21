#include "game.hpp"

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR args, int n) {
    GameRun(args);
    return 0;
}
#else
int main(int argc, char** argv) {
    GameRun(argv[1]);
    return 0;
}
#endif