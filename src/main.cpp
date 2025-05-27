#include "Asteroid.h"
#include <raylib.h>

int main()
{
    constexpr float screenW{800};
    constexpr float screenH{450};

    InitWindow(screenW, screenH, "Asteroids");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}