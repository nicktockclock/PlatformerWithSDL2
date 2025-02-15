#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"
#include "rectangle.h"
#include <cmath>

class Slope {
    public:
        Slope() {}
        Slope(Vector2 p1, Vector2 p2) :
            _p1(p1),
            _p2(p2)
        {
            if (_p2.x - _p1.x != 0){
                _slope = ((fabs(_p2.y) - fabs(_p1.y)) / ((fabs(_p2.x) - fabs(_p1.x))));
            }
        }

        const inline float getSlope() const {
            return _slope;
        }

        const bool collidesWith(const Rectangle &other) const {
            return
                (other.getRight() >= _p2.x && other.getLeft() <= _p1.x &&
                other.getTop() <= _p2.y && other.getBottom() >= _p1.y) ||

                (other.getRight() >= _p1.x && other.getLeft() <= _p2.x &&
                other.getTop() <= _p1.y && other.getBottom() >= _p2.y) ||

                (other.getLeft() <= _p1.x && other.getRight() >= _p2.x &&
                other.getTop() <= _p1.y && other.getBottom() >= _p2.y) ||

                (other.getLeft() <= _p2.x && other.getRight() >= _p1.x &&
                other.getTop() <= _p2.y && other.getBottom() >= _p1.y);
        }

        const inline Vector2 getP1() const {
            return _p1;
        }

        const inline Vector2 getP2() const {
            return _p2;
        }
    private:
        //Every slope has 2 points
        Vector2 _p1, _p2;
        //slope = (y2-y1) / (x2-x1)
        float _slope;
};

#endif