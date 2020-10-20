#include "animatedsprite.h"
#include "graphics.h"
#include <iostream>
#include <algorithm>

/* AnimatedSprite class
* Animates our sprites
*/

AnimatedSprite::AnimatedSprite(){

}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
    float posX, float posY, float timeToUpdate): Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
    _frameIndex(0),
    _timeToUpdate(timeToUpdate),
    _visible(true),
    _currentAnimationOnce(false),
    _currentAnimation(""){

}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, Direction direction){
    std::vector<SDL_Rect> rectangles;
    for (int i=0; i<frames; i++){
        SDL_Rect newRect = {x, y, width, height};
        rectangles.push_back(newRect);
        x+=width;
    }
    if (direction==LEFT){
        std::reverse(rectangles.begin(), rectangles.end());
    }
    _animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
    _offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimation(){
    _animations.clear();
    _offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once){
    _currentAnimationOnce = once;
    if (_currentAnimation!=animation){
        _currentAnimation = animation;
        _frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible){
    _visible = visible;
}

void AnimatedSprite::stopAnimation(){
    _frameIndex = 0;
    animationDone(_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime){
    Sprite::update();
    _timeElapsed += elapsedTime;
    if (_timeElapsed > _timeToUpdate){
        _timeElapsed -= _timeToUpdate;
        if (_frameIndex < _animations[_currentAnimation].size()-1){
            _frameIndex++;
        }
        else{
            if (_currentAnimationOnce == true){
                setVisible(false);
            }
            _frameIndex = 0;
            animationDone(_currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y){
    if (_visible){
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x+_offsets[_currentAnimation].x;
        destinationRectangle.y = y+_offsets[_currentAnimation].y;
        destinationRectangle.w = _sourceRect.w*globals::SPRITE_SCALE;
        destinationRectangle.h = _sourceRect.h*globals::SPRITE_SCALE;

        SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex];
        graphics.blitSurface(_spriteSheet, &sourceRect, &destinationRectangle);
    }
}
