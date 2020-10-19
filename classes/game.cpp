#include <game.h>
#include <graphics.h>
#include <input.h>
#include <SDL2/SDL.h>
#include <iostream>

/* Game class
* Handles the main game loop
*/

namespace{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5*1000/FPS;
}

Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game(){


}

void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event event;

    _level = Level("firstmap", Vector2(100, 100), graphics);
    _player = Player(graphics, _level.getPlayerSpawnPoint());
    int LAST_UPDATE_TIME = SDL_GetTicks();
    //Start the gameloop
    while (true){
        input.beginNewFrame();
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                //If this is not a held key
                if (event.key.repeat == 0){
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP){
                input.keyUpEvent(event);
            }
            else if (event.type == SDL_QUIT){
                return;
            }
            if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
                return;
            }
            else if (input.isKeyHeld(SDL_SCANCODE_A)){
                _player.moveLeft();
            }
            else if (input.isKeyHeld(SDL_SCANCODE_D)){
                _player.moveRight();
            }

            if (!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D)){
                _player.stopMoving();
            }
        }


        const int CURRENT_TIME_MS = SDL_GetTicks();
        //How long this current frame took to complete
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        draw(graphics);
    }
}

void Game::draw(Graphics &graphics){
    graphics.clear();
    _level.draw(graphics);
    _player.draw(graphics);
    graphics.flip();
}

void Game::update(float elapsedTime){
    _player.update(elapsedTime);
    _level.update(elapsedTime);

    //Check collisions
    std::vector<Rectangle> others;
    if ((others = _level.checkTileCollisions(_player.getBoundingBox())).size() > 0){
        //The player has collided with at least one tile
        _player.handleTileCollisions(others);
    }
}