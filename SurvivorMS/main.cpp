#include "stdafx.h"
#include "Game.h"
#include <windows.h> 


int main() {

    // Init Game;
    Game game;

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    game.run();


    return 0;
}