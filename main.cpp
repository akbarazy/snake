#include "raylib.h"
#include "./headers/game.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    int cellSize = 20;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);

    Game game(screenWidth, screenHeight, cellSize);

    while(!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}