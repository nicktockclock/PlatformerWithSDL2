#ifndef GRAPHICS_H
#define GRAPHICS_H

/* Graphics class
* Deals with the graphics in the game all here
*/

#include <map>
#include <string>
#include <SDL2/SDL.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics{

    public:
        Graphics();
        ~Graphics();
        /* SDL_Surface* loadImage
        * Load an image into the spritesheet map if it doesn't already exist
        * So each image should only be loaded once
        */
        SDL_Surface* loadImage(const std::string &filePath);

        /*void blitSurface
        * Draws a texture to a certain part of the screen
        */
        void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

        /* void flip
        * Renders everything to the screen
        */

        void flip();
        /* void clear
        * Clears the screen
        */
        void clear();

        /* SDL_Renderer* getRenderer
        * Returns the renderer
        */
        SDL_Renderer* getRenderer() const;
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        std::map<std::string, SDL_Surface*> _spriteSheets;

};

#endif