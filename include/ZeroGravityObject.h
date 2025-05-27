#include "Circle2D.h"
#include <raylib.h>

#ifndef ZERO_GRAVITY_OBJECT_H
#define ZERO_GRAVITY_OBJECT_H

class ZeroGravityObject : public Circle2D
{
public:
    ZeroGravityObject(float initialVelocityX = 0, float initialVelocityY = 0)
        : m_velocity{initialVelocityX, initialVelocityY}
    {
    }

    void applyVelocity(float delta);

private:
    Vector2 m_velocity{};
    // An astroid does'nt have any gravitational
    // acceleration so I don't need an acceleration Vector2
};

inline void ZeroGravityObject::applyVelocity(float delta)
{
    setX(getX() + m_velocity.x * delta);
    setY(getY() + m_velocity.y * delta);
}

#endif