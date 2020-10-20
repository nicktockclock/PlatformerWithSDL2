#ifndef SPRITE_H
#define SPRITE_H

/* Sprite class
* Holds the information for sprites
*/

#include <string>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "rectangle.h"
#include "slope.h"
#include "globals.h"

class Sprite{
    public:
        Sprite();
        Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height, float posX, float posY);
        virtual ~Sprite();
        virtual void update();
        void draw (Graphics &graphics, int x, int y);

        const Rectangle getBoundingBox() const;
        const sides::Side getCollisionSide(Rectangle &other) const;

    private:

        

    protected:
        SDL_Texture* _spriteSheet;
        SDL_Rect _sourceRect;
        float _x, _y;

        Rectangle _boundingBox;
};

#endif