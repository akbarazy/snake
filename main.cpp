#include "raylib.h"
#include <vector>

struct Position {
    int x;
    int y;
};

int main() {
    std::vector<Position> snake = {
        {5, 3},
        {5, 2},
        {5, 1},
        {4, 1},
        {3, 1},
        {2, 1},
        {2, 2},
        {1, 2}
    };
    int cellSize = 20, 
        screenWidth = 800, screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        
        for(int i = 0; i < snake.size(); i++) {
            int light = 250 - i * 25;
            DrawRectangle(
                snake[i].x * cellSize, 
                snake[i].y * cellSize, 
                cellSize, cellSize, 
                {0, 121, 241, (unsigned char)(int)light}
            );
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}