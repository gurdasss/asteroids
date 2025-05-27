#include "Asteroid.h"
#include <raylib.h>

int main()
{
    constexpr float screenW{800};
    constexpr float screenH{450};

    InitWindow(screenW, screenH, "Asteroids");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    Asteroid ast{};
    ast.setRadius(20);
    ast.setPosition(Vector2{100, 100});
    ast.setTint(RED);

    while (!WindowShouldClose())
    {

        constexpr float delta{1.0f / targetFPS};
        ast.applyVelocity(delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(ast.getPosition(), ast.getRadius(), ast.getTint());

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}