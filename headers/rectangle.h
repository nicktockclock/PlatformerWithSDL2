#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle{
    public:
        Rectangle(){}

        Rectangle(int x, int y, int width, int height) :
            _x(x),
            _y(y),
            _width(width),
            _height(height)
        {}

        const int getCenterX() const {return _x + _width / 2;}
        const int getCenterY() const {return _y + _height / 2;}

        const int getLeft() const {return _x;}
        const int getRight() const {return _x + _width;}
        const int getTop() const {return _y;}
        const int getBottom() const {return _y + _height;}

        const int getWidth() const {return _width;}
        const int getHeight() const {return _height;}

        const int getSide(const sides::Side side) const {
            return
                side == sides::TOP ? getTop() :
                side == sides::BOTTOM ? getBottom() :
                side == sides::LEFT ? getLeft() :
                side == sides::RIGHT ? getRight() :
                sides::NONE;
        }

        //bool collidesWith
        //Takes in another Rectangle and checks if the two are colliding
        const bool collidesWith(const Rectangle &other) const {
            return
                getRight() >= other.getLeft() &&
                getLeft() <= other.getRight() &&
                getTop() <= other.getBottom() &&
                getBottom() >= other.getTop();
        }

        const bool isValidRectangle() const {
            return (_x >= 0 && _y >= 0 && _width >= 0 && _height >= 0);
        }

    private:
        int _x, _y, _width, _height;
};

#endif