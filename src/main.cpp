#include "ZeroGravityObject.h"
#include "Player.h"
#include "Random.h"
#include <raylib.h>
#include <forward_list> // for std::forward_list
#include <cmath>        // for std::sin & std::cos
#include <iostream>

void initAsteroids(std::forward_list<ZeroGravityObject> &asteroids);
void repositionAsteroid(ZeroGravityObject &asteroid);
void splitAsteroid(const ZeroGravityObject &asteroid, std::forward_list<ZeroGravityObject> &asteroids);

void asteroidCollisionWithProjectiles(const ZeroGravityObject &asteroid, std::forward_list<ZeroGravityObject> &asteroids, std::forward_list<ZeroGravityObject> &projectiles);

Vector2 degreeToVelocity(float degree, float speed);

int main()
{
    constexpr float screenW{800};
    constexpr float screenH{450};

    InitWindow(screenW, screenH, "Asteroids");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    std::forward_list<ZeroGravityObject> asteroids{};
    initAsteroids(asteroids);

    std::forward_list<ZeroGravityObject> projectiles{};

    Player player{20};
    player.setPosition(Vector2{screenW / 2, screenH / 2});
    player.setColor(RED);

    while (!WindowShouldClose())
    {

        constexpr float minDegree{0};
        constexpr float maxDegree{360};

        // clamp the rotation
        if (player.getRotation() < minDegree)
            player.setRotation(maxDegree);
        else if (player.getRotation() > maxDegree)
            player.setRotation(minDegree);

        constexpr float rotationalSpeed{5};

        if (IsKeyDown(KEY_LEFT))
            player.setRotation(player.getRotation() - rotationalSpeed);
        else if (IsKeyDown(KEY_RIGHT))
            player.setRotation(player.getRotation() + rotationalSpeed);

        if (IsKeyPressed(KEY_SPACE))
        {
            // it worked for some reason when I inverted
            // the degree

            float angleInDegree{-player.getRotation()};
            constexpr float speed{200};

            ZeroGravityObject projectile{degreeToVelocity(angleInDegree, speed)};

            projectile.setPosition(player.getPosition());
            projectile.setRadius(5);
            projectile.setTint(BLUE);

            projectiles.push_front(projectile);
        }

        constexpr float delta{1.0f / targetFPS};

        // maybe I can use a while loop here!!

        auto previousProjectile{projectiles.before_begin()};
        auto projectile{projectiles.begin()};
        auto previousAsteroid{asteroids.before_begin()};
        auto asteroid{asteroids.begin()};

        while (asteroid != asteroids.cend() || projectile != projectiles.cend())
        {
            // update all asteroids if ONLY asteroid list is non-empty
            // update all projectile if ONLY projectile list is non-empty
            // break

            if (asteroid != asteroids.cend())
            {
                asteroid->applyVelocity(delta);
                repositionAsteroid(*asteroid);

                ++previousAsteroid;
                ++asteroid;
            }

            if (projectile != projectiles.cend())
            {
                projectile->applyVelocity(delta);

                ++previousProjectile;
                ++projectile;
            }
        }

        // for (ZeroGravityObject &asteroid : asteroids)
        // {
        //     asteroid.applyVelocity(delta);
        //     repositionAsteroid(asteroid);
        //     asteroidCollisionWithProjectiles(asteroid, asteroids, projectiles);
        // }

        // auto previousProjectile{projectiles.before_begin()};
        // for (auto projectile{projectiles.begin()};
        //      projectile != projectiles.cend();
        //      ++projectile)
        // {
        //     projectile->applyVelocity(delta);

        //     if (
        //         (projectile->getX() > screenW + projectile->getRadius()) ||
        //         (projectile->getX() < -projectile->getRadius()) ||
        //         (projectile->getY() > screenH + projectile->getRadius()) ||
        //         (projectile->getY() < -projectile->getRadius()))
        //     {
        //         projectile = projectiles.erase_after(previousProjectile);

        //         if (projectile == projectiles.cend())
        //             break;
        //     }

        //     ++previousProjectile;
        // }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const ZeroGravityObject &asteroid : asteroids)
            DrawCircleV(asteroid.getPosition(),
                        asteroid.getRadius(),
                        asteroid.getTint());

        for (const ZeroGravityObject &projectile : projectiles)
            DrawCircleV(projectile.getPosition(),
                        projectile.getRadius(),
                        projectile.getTint());

        player.draw();

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
        constexpr float speed{100};
        float randomDegree{static_cast<float>(Random::get(0, 360))};

        ZeroGravityObject bigAsteroid{
            degreeToVelocity(
                randomDegree,
                speed)};

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
        constexpr float speed{100};
        float randomDegree{static_cast<float>(Random::get(0, 360))};

        ZeroGravityObject dividedAsteroid{degreeToVelocity(
            randomDegree, speed)};

        dividedAsteroid.setRadius(asteroid.getRadius() / 2.0f);
        dividedAsteroid.setPosition(asteroid.getPosition());
        dividedAsteroid.setTint(asteroid.getTint());

        asteroids.push_front(dividedAsteroid);
    }
}

Vector2 degreeToVelocity(float degree, float speed)
{
    float angleInRadian{(degree * PI) / 180};

    return Vector2{
        speed * std::cos(angleInRadian),
        -speed * std::sin(angleInRadian)};
}

void asteroidCollisionWithProjectiles(const ZeroGravityObject &asteroid, std::forward_list<ZeroGravityObject> &asteroids, std::forward_list<ZeroGravityObject> &projectiles)
{
    if (projectiles.empty() || asteroids.empty())
        return;

    auto previousProjectile{projectiles.before_begin()};
    for (auto projectile{projectiles.begin()};
         projectile != projectiles.cend();
         ++projectile)
    {
        if (CheckCollisionCircles(asteroid.getPosition(),
                                  asteroid.getRadius(),
                                  projectile->getPosition(),
                                  projectile->getRadius()))
        {
            projectile = projectiles.erase_after(previousProjectile);

            if (projectile == projectiles.cend())
                return;
        }

        ++previousProjectile;
    }
}