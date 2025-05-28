#include "ZeroGravityObject.h"
#include "Triangle2D.h"
#include "Random.h"
#include <raylib.h>
#include <forward_list> // for std::forward_list
#include <cmath>        // for std::sin & std::cos

void initAsteroids(std::forward_list<ZeroGravityObject> &asteroids);
void repositionAsteroid(ZeroGravityObject &asteroid);
void splitAsteroid(const ZeroGravityObject &asteroid, std::forward_list<ZeroGravityObject> &asteroids);

Vector2 randomVelocity();

int main()
{
    constexpr float screenW{800};
    constexpr float screenH{450};

    InitWindow(screenW, screenH, "Asteroids");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    std::forward_list<ZeroGravityObject> asteroids{};
    initAsteroids(asteroids);

    Triangle2D player{};
    player.setTint(RED);

    while (!WindowShouldClose())
    {

        constexpr float delta{1.0f / targetFPS};

        for (ZeroGravityObject &asteroid : asteroids)
        {
            asteroid.applyVelocity(delta);
            repositionAsteroid(asteroid);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const ZeroGravityObject &asteroid : asteroids)
            DrawCircleV(asteroid.getPosition(),
                        asteroid.getRadius(),
                        asteroid.getTint());

        DrawTriangle(player.getPoint1(),
                     player.getPoint2(),
                     player.getPoint3(),
                     player.getTint());

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void initAsteroids(std::forward_list<ZeroGravityObject> &asteroids)
{
    for (auto i{0}; i < 5; ++i)
    {

        ZeroGravityObject bigAsteroid{randomVelocity().x,
                                      randomVelocity().y};

        bigAsteroid.setPosition(Vector2{
            static_cast<float>(Random::get(0, GetScreenWidth())),
            static_cast<float>(Random::get(0, GetScreenHeight())),
        });

        bigAsteroid.setRadius(50);

        bigAsteroid.setTint(DARKGRAY);

        asteroids.push_front(bigAsteroid);
    }
}

void repositionAsteroid(ZeroGravityObject &asteroid)
{
    int screenW{GetScreenWidth()};
    int screenH{GetScreenHeight()};

    // Check if an asteroid cross the following edges:

    // BOTTOM-EDGE
    if (asteroid.getY() > static_cast<float>(screenH) + asteroid.getRadius())
    {
        asteroid.setPosition(Vector2{
            static_cast<float>(Random::get(0, screenW)),
            -asteroid.getRadius(),
        });
    }
    // TOP-EDGE
    else if (asteroid.getY() < -asteroid.getRadius())
    {
        asteroid.setPosition(Vector2{
            static_cast<float>(Random::get(0, screenW)),
            static_cast<float>(screenH) + asteroid.getRadius(),
        });
    }

    // RIGHT-EDGE
    if (asteroid.getX() > static_cast<float>(screenW) + asteroid.getRadius())
    {
        asteroid.setPosition(Vector2{
            -asteroid.getRadius(),
            static_cast<float>(Random::get(0, screenH)),
        });
    }
    // LEFT-EDGE
    else if (asteroid.getX() < -asteroid.getRadius())
    {
        asteroid.setPosition(Vector2{
            static_cast<float>(screenW) + asteroid.getRadius(),
            static_cast<float>(Random::get(0, screenH)),
        });
    }
}

void splitAsteroid(const ZeroGravityObject &asteroid, std::forward_list<ZeroGravityObject> &asteroids)
{
    if (asteroids.empty())
        return;

    for (auto i{0}; i < 2; ++i)
    {
        ZeroGravityObject dividedAsteroid{randomVelocity().x,
                                          randomVelocity().y};

        dividedAsteroid.setRadius(asteroid.getRadius() / 2.0f);
        dividedAsteroid.setPosition(asteroid.getPosition());
        dividedAsteroid.setTint(asteroid.getTint());

        asteroids.push_front(dividedAsteroid);
    }
}

Vector2 randomVelocity()
{
    float angleInDegree{static_cast<float>(Random::get(0, 360))};
    float angleInRadian{(angleInDegree * PI) / 180};
    constexpr float speed{100};

    return Vector2{
        speed * std::cos(angleInRadian),
        -speed * std::sin(angleInRadian)};
}