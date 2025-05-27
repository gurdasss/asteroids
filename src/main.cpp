#include "ZeroGravityObject.h"
#include "Random.h"
#include <raylib.h>
#include <forward_list>
#include <cmath>

void initAsteroids(std::forward_list<ZeroGravityObject> &asteroids);

int main()
{
    constexpr float screenW{800};
    constexpr float screenH{450};

    InitWindow(screenW, screenH, "Asteroids");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    std::forward_list<ZeroGravityObject> asteroids{};
    initAsteroids(asteroids);

    while (!WindowShouldClose())
    {

        [[maybe_unused]] constexpr float delta{1.0f / targetFPS};

        for (ZeroGravityObject &asteroid : asteroids)
            asteroid.applyVelocity(delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const ZeroGravityObject &asteroid : asteroids)
            DrawCircleV(asteroid.getPosition(),
                        asteroid.getRadius(),
                        asteroid.getTint());

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
        float angleInDegree{static_cast<float>(Random::get(0, 360))};
        float angleInRadian{(angleInDegree * PI) / 180};
        constexpr float speed{100};

        ZeroGravityObject asteroid{
            speed * std::cos(angleInRadian),
            -speed * std::sin(angleInRadian)};

        asteroid.setPosition(Vector2{
            static_cast<float>(Random::get(0, GetScreenWidth())),
            static_cast<float>(Random::get(0, GetScreenHeight())),
        });
        constexpr float asteroidRadius{50};

        asteroid.setRadius(asteroidRadius);

        asteroid.setTint(DARKGRAY);

        asteroids.push_front(asteroid);
    }
}