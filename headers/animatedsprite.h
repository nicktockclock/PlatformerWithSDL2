#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "globals.h"
#include <map>
#include <string>
#include <vector>

class Graphics;

/* Animated Sprite class
* Holds the logic for animating our sprites
*/

class AnimatedSprite : public Sprite{
    public:
        AnimatedSprite();
        AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
            float posX, float posY, float timeToUpdate);
        /* void playAnimation
        * Play animation as long as it's not already playing
        */
        void playAnimation(std::string animation, bool once = false);

        /* void update
        * Updates the animated sprite
        */
        void update(int elapsedTime);

        /* void draw
        * Draws the sprite to the screen
        */
        void draw(Graphics &graphics, int x, int y);

        

    private:
        std::map<std::string, std::vector<SDL_Rect>> _animations;
        std::map<std::string, Vector2> _offsets;

        int _frameIndex;
        double _timeElapsed;
        bool _visible;

    protected:
        double _timeToUpdate;
        bool _currentAnimationOnce;
        std::string _currentAnimation;

        /* void setupAnimation
        * A required function that set up all animations for a sprite
        */
        virtual void setupAnimations() = 0;

        /* void addAnimation
        * Adds an animation to our map of animations for this sprite
        */
        void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, Direction direction);

        /* void resetAnimation
        * Resets the map of animations for this sprite
        */
        void resetAnimation();

        /* void stopAnimation
        * Stops playing the animation
        */
        void stopAnimation();

        /* void setVisible
        * Sets the animation currently playing to be visible
        */
        void setVisible(bool visible);

        /* void animationDone
        * Stuff that plays when an animation is done
        */
        virtual void animationDone(std::string currentAnimation) = 0;
};

#endif