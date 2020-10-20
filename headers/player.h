#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include <string>

class Graphics;

/* Player class
* Holds the logic animating our player character
*/

class Player: public AnimatedSprite{
    public:
        Player();
        Player(Graphics &graphics, Vector2 spawnPoint);
        void draw(Graphics &Graphics);
        void update(float elapsedTime);

        /* void moveLeft
        * Moves the player to the left by -dx
        */
        void moveLeft();

        /* void moveRight
        * Moves the player to the right by dx
        */
        void moveRight();

        /* void stopMoving
        * Stops the player and play idle animation
        */
        void stopMoving();

        /* void jump
        * Handles jumping
        */
        void jump();

        /* void jetpackMovement
        * Handles jetpack movement
        */
        void jetpackMovement(Direction direction);

        /* void turnOffJetpack
        * Turn off the players jetpack
        */
        void turnOffJetpack();

        virtual void animationDone(std::string currentAnimation);
        virtual void setupAnimations();

        /* void handleTileCollisions
        * Handles collisions with any tiles the player is standing on
        */
        void handleTileCollisions(std::vector<Rectangle> &others);

        /* void handleSlopeCollisions
        * Handles collisions with any slopes the player is standing on
        */
        void handleSlopeCollisions(std::vector<Slope> &others);

        const float getX() const;
        const float getY() const;
        const bool isJumping() const;
        const bool jetpackOn() const;

    private:
        float _dx, _dy;

        Direction _facing;
        //True if standing on the ground
        bool _grounded;
        bool _jetpack;
        bool _jumping;
};

#endif