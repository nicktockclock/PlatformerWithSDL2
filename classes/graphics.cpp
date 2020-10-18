#include <graphics.h>
#include <globals.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

/* Graphics class
* Deals with the graphics in the game all here
*/

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGTH, 0, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "PlatformerJetpack?");

}

Graphics::~Graphics(){
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath){
    if (_spriteSheets.count(filePath)==0){
        _spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
    SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip(){
    SDL_RenderPresent(_renderer);
}

void Graphics::clear(){
    SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const{
    return _renderer;
}