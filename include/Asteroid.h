#include "Circle2D.h"
#include <raylib.h>

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid : public Circle2D
{
public:
    Asteroid(float initialVelocityX = 0, float initialVelocityY = 0)
        : m_velocity{initialVelocityX, initialVelocityY}
    {
    }

    void applyVelocity(float delta);

private:
    Vector2 m_velocity{};
    // An astroid does'nt have any gravitational
    // acceleration so I don't need an acceleration Vector2
};

inline void Asteroid::applyVelocity(float delta)
{
    setX(getX() + m_velocity.x * delta);
    setY(getY() + m_velocity.y * delta);
}

#endif