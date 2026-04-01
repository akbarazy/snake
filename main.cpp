#include "raylib.h"
#include "headers/game.h"

int main() {
    InitWindow(700, 750, "Snake - C++ & Raylib Game");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}