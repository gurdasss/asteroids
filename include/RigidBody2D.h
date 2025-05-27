#include <raylib.h>

#ifndef RIGID_BODY_2D_H
#define RIGID_BODY_2D_H

class RigidBody2D
{
public:
    void setVelocityX(float velocityX) { m_velocity.x = velocityX; }
    void setVelocityY(float velocityY) { m_velocity.y = velocityY; }

    float getVelocityX() const { return m_velocity.x; }
    float getVelocityY() const { return m_velocity.y; }

    void setAccelerationX(float accelerationX) { m_acceleration.x = accelerationX; }
    void setAccelerationY(float accelerationY) { m_acceleration.y = accelerationY; }

    float getAccelerationX() const { return m_acceleration.x; }
    float getAccelerationY() const { return m_acceleration.y; }

private:
    Vector2 m_velocity{};
    Vector2 m_acceleration{0, 9.8f};
};

#endif