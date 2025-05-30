#include <raylib.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(float radius)
        : m_radius{radius} {}

    void setRotation(float rotation) { m_rotation = rotation; }
    float getRotation() const { return m_rotation; }

    void setPosition(const Vector2 &position) { m_center = position; }
    Vector2 getPosition() const { return m_center; }

    void setColor(const Color &color) { m_color = color; }

    void draw() const
    {
        // we can call non-const non-member function
        // because we're passing member variables by values

        DrawPoly(m_center, 3, m_radius, m_rotation, m_color);
    }

private:
    Vector2 m_center{};
    float m_rotation{};
    float m_radius{};
    Color m_color{};
};

#endif