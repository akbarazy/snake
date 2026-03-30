#include "raylib.h"
#include "headers/game.h"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}