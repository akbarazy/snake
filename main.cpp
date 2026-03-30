#include "raylib.h"
#include "./headers/game.h"

int main() {
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Snake Game OOP");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        ClearBackground(DARKGREEN);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}