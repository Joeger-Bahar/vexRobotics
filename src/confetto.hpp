#pragma once

#include <iostream>
#include <cmath>
#include "math.hpp"

#include "main.h"

enum Shapes
{
    circle = 0,
    rect,
    shapesLength = 2
};

class Confetto
{
public:
    Confetto(int x, int y, uint32_t color, Vector2&& velocity, Shapes shape) : rect({ x, y, 10, 4 }), color(color), velocity({ velocity.x, velocity.y }), shape(shape)
    {}
    void updateCoords()
    {
        this->rect.x += this->velocity.x;
        this->rect.y += this->velocity.y;
    }
    void render()
    {
        pros::screen::set_pen(this->color);
        if (this->shape == Shapes::rect)
            pros::screen::fill_rect(this->rect.x, this->rect.y, this->rect.x + this->rect.w, this->rect.y + this->rect.h);
        else if (this->shape == Shapes::circle)
            pros::screen::fill_circle(this->rect.x, this->rect.y, 5);
    }
    void rotate(int angle)
    {
        this->rect.x = cos(angle) * this->rect.x - sin(angle) * this->rect.y;
        this->rect.y = sin(angle) * this->rect.x + cos(angle) * this->rect.y;
    }

    Vector2 velocity;
    Rect rect;
    Shapes shape;
    
private:
    uint32_t color;
};
