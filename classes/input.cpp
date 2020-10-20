#include "input.h"

/* Input class
* Handles all of the user input for the game
*/

//Gets called at the beginning of each new frame to reset the keys
void Input::beginNewFrame(){
    _pressedKeys.clear();
    _releasedKeys.clear();
}

//Set to true for key being pressed or held
void Input::keyDownEvent(const SDL_Event& event){
    _pressedKeys[event.key.keysym.scancode] = true;
    _heldKeys[event.key.keysym.scancode] = true;
}

//Set to true for key being released, and held to false
void Input::keyUpEvent(const SDL_Event& event){
    _releasedKeys[event.key.keysym.scancode] = true;
    _heldKeys[event.key.keysym.scancode] = false;
}

//Check if key was pressed during current frame
bool Input::wasKeyPressed(SDL_Scancode key){
    return _pressedKeys[key];
}

//Check if key was pressed during current frame
bool Input::wasKeyReleased(SDL_Scancode key){
    return _releasedKeys[key];
}

//Check if key is being held
bool Input::isKeyHeld(SDL_Scancode key){
    return _heldKeys[key];
}