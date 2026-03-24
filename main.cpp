#include "raylib.h"
#include <vector>

struct Position {int x, y;};
enum Direction {UP, DOWN, LEFT, RIGHT};

int main() {
    Position head = {5, 1};
    std::vector<Position> snake = {
        {5, 1}, 
        {4, 1}, 
        {3, 1}, 
        {2, 1}, 
        {1, 1}
    };
    Direction prevDir = RIGHT, currentDir = RIGHT;
    int cellSize = 20, screenWidth = 800, screenHeight = 600,
        framesRate = 60, framesCounter = 0, snakeSpeed = framesRate / 4;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(framesRate);

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_UP) && prevDir != DOWN) currentDir = UP;
        if(IsKeyPressed(KEY_DOWN) && prevDir != UP) currentDir = DOWN;
        if(IsKeyPressed(KEY_LEFT) && prevDir != RIGHT) currentDir = LEFT;
        if(IsKeyPressed(KEY_RIGHT) && prevDir != LEFT) currentDir = RIGHT;

        if(framesCounter == snakeSpeed) {
            framesCounter = 0;
            prevDir = currentDir;

            switch(currentDir) {
                case UP:
                    head.y--; 
                    break;

                case DOWN:
                    head.y++; 
                    break;

                case LEFT:
                    head.x--; 
                    break;

                case RIGHT:
                    head.x++; 
                    break;
            }

            snake.insert(snake.begin(), head);
            snake.pop_back();
        } else {
            framesCounter++;
        }

        BeginDrawing();
        ClearBackground({155, 155, 155, 255});

        for(int x = 0; x < screenWidth / cellSize; x++) {
            for(int y = 0; y < screenHeight / cellSize; y++) {
                if(x % 2 && y % 2) {
                    DrawRectangle(
                        x * cellSize, 
                        y * cellSize, 
                        cellSize, cellSize, 
                        {185, 185, 185, 255}
                    );
                } else if(x % 2 == 0 && y % 2 == 0) {
                    DrawRectangle(
                        x * cellSize, 
                        y * cellSize, 
                        cellSize, cellSize, 
                        {185, 185, 185, 255}
                    );
                }
            }
        }
        
        for(int i = 0; i < snake.size(); i++) {
            int light = 255 - i * (255 / snake.size());
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