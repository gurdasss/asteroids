#include "Circle2D.h"
#include <raylib.h>

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid : public Circle2D
{
public:
    void setInitialVelocityX(float initialVelocityX) { m_velocity.x = initialVelocityX; }
    void setInitialVelocityY(float initialVelocityY) { m_velocity.y = initialVelocityY; }

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