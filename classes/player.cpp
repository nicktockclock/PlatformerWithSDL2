#include "player.h"
#include "graphics.h"
#include <iostream>


namespace player_constants{
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 0.7f;
    const float JETPACK_SPEED = 0.4f;

    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint):
    AnimatedSprite(graphics, "content/sprites/herochar_spritesheet.png", 0, 64, 16, 16, spawnPoint.x, spawnPoint.y, 100),
    _dx(0),
    _dy(0),
    _facing(RIGHT),
    _grounded(false)
{
    graphics.loadImage("content/sprites/herochar_spritesheet.png");
    setupAnimations();
    playAnimation("idleRight");
    _facing = RIGHT;
    _jetpack = false;
    _jumping = false;
}

void Player::setupAnimations(){
    addAnimation(4, 0, 64, "idleRight", 16, 16, Vector2(0, 0), RIGHT);
    addAnimation(4, 64, 272, "idleLeft", 16, 16, Vector2(0, 0), LEFT);
    addAnimation(6, 0, 16, "runRight", 16, 16, Vector2(0, 0), RIGHT);
    addAnimation(6, 32, 224, "runLeft", 16, 16, Vector2(0, 0), LEFT);
}

void Player::animationDone(std::string currentAnimation){

}

const float Player::getX() const{
    return _x;
}

const float Player::getY() const{
    return _y;
}

const bool Player::isJumping() const{
    return _jumping;
}

const bool Player::jetpackOn() const{
    return _jetpack;
}

void Player::update(float elapsedTime){
    if (_jetpack){
        //Move by dx
        _x += _dx * elapsedTime;
        //Move by _dy
        _y += _dy * elapsedTime;
    }
    else {
        //Apply gravity
        if (_dy <= player_constants::GRAVITY_CAP){
            _dy += player_constants::GRAVITY * elapsedTime;
        }

        //Move by dx
        _x += _dx * elapsedTime;
        //Move by _dy
        _y += _dy * elapsedTime;
    }
    
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

void Player::turnOffJetpack(){
    _dy = player_constants::GRAVITY;
    _jetpack = false;
}

void Player::jump(){
    if (_grounded){
        _dy = 0;
        _dy -= player_constants::JUMP_SPEED;
        _grounded = false;
        _jumping = true;
    }
}

void Player::jetpackMovement(Direction direction){
    _dx = -player_constants::JETPACK_SPEED;
    _dy = 0;
    playAnimation("runLeft");
    _facing = LEFT;
    _jetpack = true;
}

void Player::handleTileCollisions(std::vector<Rectangle> &others){
    //Figure out what side the collision is on and move the player out
    for (int i = 0; i < others.size(); i++){
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE){
            switch (collisionSide){
                case sides::TOP:
                    _dy = 0;
                    _y = others.at(i).getBottom() +1;
                    if (_grounded){
                        _dx = 0;
                        _x -= _facing == RIGHT ? 1.0f : -1.0f;
                    }
                    break;
                case sides::BOTTOM:
                    _y = others.at(i).getTop() - _boundingBox.getHeight() -1;
                    _dy = 0;
                    _grounded = true;
                    _jumping = false;
                    break;
                case sides::LEFT:
                    _x = others.at(i).getRight() +1;
                    break;
                case sides::RIGHT:
                    _x = others.at(i).getLeft() - _boundingBox.getWidth() -1;
                    break;
            }
        }
    }
}

void Player::handleSlopeCollisions(std::vector<Slope> &others){
    for (int i = 0; i < others.size(); i++){
        //Calculate where on the slope the players bottom center is touching
        //Use y=mx+b to calculate the y position to place the player
        //First calculate 'b' (the y intercept) with b=y-mx using one of the points for this slope
        int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

        //Now get the players center x
        int centerX = _boundingBox.getCenterX();

        //Now pass these values into y=mx+b to the the new y position to place the player
        int newY = (others.at(i).getSlope() * centerX) + b - 8; //8 is temporary to fix a problem with janky slopes

        //Now reposition the player to the correct y
        if (_grounded){
            _y = newY - _boundingBox.getHeight();
            _grounded = true;
        }
        
    }
}

