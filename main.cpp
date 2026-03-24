#include "raylib.h"
#include <vector>

struct Position {int x, y;};
enum Direction {UP, DOWN, LEFT, RIGHT};

int main() {
    std::vector<Position> snake = {
        {6, 2}, 
        {5, 2}, 
        {4, 2}, 
        {3, 2}, 
        {2, 2}
    };
    Position head = snake[0],
        leftEye = {10, 3}, rightEye = {10, 12};
    Direction prevDir = RIGHT, currentDir = RIGHT;
    int cellSize = 20, screenWidth = 800, screenHeight = 600,
        framesRate = 60, framesCounter = 0, snakeSpeed = framesRate / 5;
    bool grow = false;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(framesRate);

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_G)) grow = true;
        if(IsKeyPressed(KEY_UP) && prevDir != DOWN) currentDir = UP;
        if(IsKeyPressed(KEY_DOWN) && prevDir != UP) currentDir = DOWN;
        if(IsKeyPressed(KEY_LEFT) && prevDir != RIGHT) currentDir = LEFT;
        if(IsKeyPressed(KEY_RIGHT) && prevDir != LEFT) currentDir = RIGHT;

        if(framesCounter == snakeSpeed) {
            switch(currentDir) {
                case UP:
                    head.y--; 
                    leftEye = {3, 5};
                    rightEye = {12, 5};
                    break;

                case DOWN:
                    head.y++; 
                    leftEye = {3, 10};
                    rightEye = {12, 10};
                    break;

                case LEFT:
                    head.x--; 
                    leftEye = {5, 3};
                    rightEye = {5, 12};
                    break;

                case RIGHT:
                    head.x++; 
                    leftEye = {10, 3};
                    rightEye = {10, 12};
                    break;
            }

            snake.insert(snake.begin(), head);
            if(!grow) snake.pop_back();

            framesCounter = 0;
            prevDir = currentDir;
            grow = false;
        } else {
            framesCounter++;
        }

        BeginDrawing();
        ClearBackground({150, 150, 150, 255});

        for(int x = 2; x < (screenWidth / cellSize) - 2; x++) {
            for(int y = 2; y < (screenHeight / cellSize) - 2; y++) {
                if(x % 2) {
                    if(y % 2) {
                        DrawRectangle(
                            x * cellSize, 
                            y * cellSize, 
                            cellSize, cellSize, 
                            {150, 195, 65, 255}
                        );
                    } else {
                        DrawRectangle(
                            x * cellSize, 
                            y * cellSize, 
                            cellSize, cellSize, 
                            {170, 215, 81, 255}
                        );
                    }
                } else if(x % 2 == 0) {
                    if(y % 2 == 0) {
                        DrawRectangle(
                            x * cellSize, 
                            y * cellSize, 
                            cellSize, cellSize, 
                            {150, 195, 65, 255}
                        );
                    } else {
                        DrawRectangle(
                            x * cellSize, 
                            y * cellSize, 
                            cellSize, cellSize, 
                            {170, 215, 81, 255}
                        );
                    }
                }
            }
        }
        
        for(int i = 0; i < snake.size(); i++) {
            int light = 255 - i * ((255 - 75) / snake.size());
            DrawRectangle(
                snake[i].x * cellSize, 
                snake[i].y * cellSize, 
                cellSize, cellSize, 
                {0, 121, 241, (unsigned char)(int)light}
            );

            if(i == 0) {
                DrawRectangle(
                    snake[0].x * cellSize + leftEye.x, 
                    snake[0].y * cellSize + leftEye.y, 
                    5, 5, RAYWHITE
                );
                DrawRectangle(
                    snake[0].x * cellSize + rightEye.x, 
                    snake[0].y * cellSize + rightEye.y, 
                    5, 5, RAYWHITE
                );
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}