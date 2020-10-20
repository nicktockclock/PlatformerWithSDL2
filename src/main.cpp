
#include <iostream>
#include "game.h"
#include <SDL2/SDL.h>

/* Main
* Entry point for the game
*/


int main(int argc, char *argv[]) {
    //std::cout << "Hello Easy C++ project!" << std::endl;
    Game game;
    game.gameLoop();
    return 0;
}