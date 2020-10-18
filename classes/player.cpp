#include <player.h>
#include <graphics.h>


namespace player_constants{
    const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y):
    AnimatedSprite(graphics, "content/sprites/herochar_spritesheet.png", 0, 64, 16, 16, x, y, 100)
{
    graphics.loadImage("content/sprites/herochar_spritesheet.png");
    setupAnimations();
    playAnimation("idleRight");
    _facing = RIGHT;
}

void Player::setupAnimations(){
    addAnimation(4, 0, 64, "idleRight", 16, 16, Vector2(0, 0), RIGHT);
    addAnimation(4, 64, 272, "idleLeft", 16, 16, Vector2(0, 0), LEFT);
    addAnimation(6, 0, 16, "runRight", 16, 16, Vector2(0, 0), RIGHT);
    addAnimation(6, 32, 224, "runLeft", 16, 16, Vector2(0, 0), LEFT);
}

void Player::animationDone(std::string currentAnimation){

}

void Player::update(float elapsedTime){
    //Move by dx
    _x += _dx * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
    AnimatedSprite::draw(graphics, _x, _y);
}

void Player::moveLeft(){
    _dx = -player_constants::WALK_SPEED;
    playAnimation("runLeft");
    _facing = LEFT;
}

void Player::moveRight(){
    _dx = player_constants::WALK_SPEED;
    playAnimation("runRight");
    _facing = RIGHT;
}

void Player::stopMoving(){
    _dx = 0.0f;
    playAnimation(_facing==RIGHT ? "idleRight" : "idleLeft");
}

