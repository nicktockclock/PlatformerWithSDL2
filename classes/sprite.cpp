#include "sprite.h"
#include "globals.h"

Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
    float posX, float posY): _x(posX), _y(posY){
    _sourceRect.x = sourceX;
    _sourceRect.y = sourceY;
    _sourceRect.w = width;
    _sourceRect.h = height;

    _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (_spriteSheet==NULL){
        printf("\nError: unable to load image\n");
    }
    _boundingBox = Rectangle(_x, _y, width*globals::SPRITE_SCALE, height*globals::SPRITE_SCALE);
}

Sprite::~Sprite(){}

void Sprite::draw(Graphics &graphics, int x, int y){
    SDL_Rect destinationRectangle = {x, y, _sourceRect.w*globals::SPRITE_SCALE, _sourceRect.h*globals::SPRITE_SCALE};
    graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

void Sprite::update(){
    _boundingBox = Rectangle(_x, _y, _sourceRect.w*globals::SPRITE_SCALE, _sourceRect.h*globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const{
    return _boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = getBoundingBox().getRight() - other.getLeft();
    amtLeft = other.getRight() - getBoundingBox().getLeft();
    amtTop = other.getBottom() - getBoundingBox().getTop();
    amtBottom = getBoundingBox().getBottom() - other.getTop();

    int lowest = std::min({abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)});
    return
        lowest == abs(amtRight) ? sides::RIGHT :
        lowest == abs(amtLeft) ? sides::LEFT :
        lowest == abs(amtTop) ? sides::TOP :
        lowest == abs(amtBottom) ? sides::BOTTOM :
        sides::NONE;
}