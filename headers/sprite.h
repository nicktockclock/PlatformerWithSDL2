#ifndef SPRITE_H
#define SPRITE_H

/* Sprite class
* Holds the information for sprites
*/

#include <string>
#include <SDL2/SDL.h>
#include <graphics.h>

class Sprite{
    public:
        Sprite();
        Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, float posX, float posY);
        virtual ~Sprite();
        virtual void update();
        void draw (Graphics &graphics, int x, int y);

    private:

        

    protected:
        SDL_Texture* _spriteSheet;
        SDL_Rect _sourceRect;
        float _x, _y;
};

#endif