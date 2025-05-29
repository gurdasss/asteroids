#include "Triangle2D.h"
#include <raylib.h>
#include <raymath.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(float width, float height)
        : m_width{width},
          m_height{height} {}

    void setRotation(float rotation) { m_rotation = rotation; }
    float getRotation() const { return m_rotation; }

    void setPosition(const Vector2 &position);
    Vector2 getPosition() const;

    void setColor(const Color &color) { m_shape.setTint(color); }

    void draw() const;

private:
    Triangle2D m_shape{};
    float m_rotation{};
    float m_width{};
    float m_height{};
};

// member functions defined outside
// the class definition are'nt inline
// by default

inline void Player::draw() const
{
    // we can call non-const non-member function
    // because we're passing member variables by values
    DrawTriangle(m_shape.getPoint1(),
                 m_shape.getPoint2(),
                 m_shape.getPoint3(),
                 m_shape.getTint());
}

inline void Player::setPosition(const Vector2 &position)
{
    m_shape.setPoint1(position);
    m_shape.setPoint2(Vector2Add(m_shape.getPoint1(),
                                 Vector2{-m_width, m_height}));

    m_shape.setPoint3(Vector2Add(m_shape.getPoint2(),
                                 Vector2{m_width * 2, 0}));
}

#endif