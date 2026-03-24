#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>

struct Position { int x, y; };
enum Direction { UP, DOWN, LEFT, RIGHT };

bool isPositionFree(
    const std::vector<Position> &snake,
    const std::vector<Position> &food,
    Position position
);
Position generatePosition(
    const std::vector<Position> &snake,
    const std::vector<Position> &food,
    int gridWidth,
    int gridHeight
);

int main() {
    int cellSize = 20;
    int screenWidth = 800;
    int screenHeight = 600;

    int gridWidth = screenWidth / cellSize;
    int gridHeight = screenHeight / cellSize;

    int totalCells = (gridWidth - 4) * (gridHeight - 4);
    int usedCells, freeCells;

    int framesRate = 60;
    int framesCounter = 0;
    int snakeSpeed = framesRate / 5;

    int maxFood = 10;
    float foodTimer = 0.0f;
    float foodDelay = 3.0f; 

    bool grow = false;

    std::vector<Position> snake = {
        {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}
    };
    std::vector<Position> food;

    srand(time(0));
    for(int i = 0; i < 3; i++) {
        food.push_back(
            generatePosition(snake, food, gridWidth, gridHeight)
        );
    }

    Position head = snake[0];
    Position leftEye = {10, 3};
    Position rightEye = {10, 12};

    Direction prevDir = RIGHT;
    Direction currentDir = RIGHT;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(framesRate);

    while(!WindowShouldClose()) {
        foodTimer += GetFrameTime();

        if(IsKeyPressed(KEY_UP) && prevDir != DOWN) currentDir = UP;
        if(IsKeyPressed(KEY_DOWN) && prevDir != UP) currentDir = DOWN;
        if(IsKeyPressed(KEY_LEFT) && prevDir != RIGHT) currentDir = LEFT;
        if(IsKeyPressed(KEY_RIGHT) && prevDir != LEFT) currentDir = RIGHT;

        if(framesCounter == snakeSpeed) {
            head = snake[0];
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

            if(
                snake[0].x < 2 || snake[0].x > (gridWidth - 2) ||
                snake[0].y < 2 || snake[0].y > (gridHeight - 2)
            ) CloseWindow();

            for(size_t i = 1; i < snake.size(); i++) {
                if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    CloseWindow();
                }
            }

            for(size_t i = 0; i < food.size(); i++) {
                if(head.x == food[i].x && head.y == food[i].y) {
                    grow = true;
                    food.erase(food.begin() + i);
                    
                    if(snake.size() < totalCells) 
                        food.push_back(generatePosition(snake, food, gridWidth, gridHeight));
                    break;
                }
            }

            if(!grow) snake.pop_back();

            grow = false;
            prevDir = currentDir;
            framesCounter = 0;
        } else {
            framesCounter++;
        }

        usedCells = snake.size() + food.size();
        freeCells = totalCells - usedCells;

        // ✅ PERBAIKAN DI SINI (SMART FOOD RESPAWN)
        int targetFood = (freeCells < maxFood) ? freeCells : maxFood;

        if(foodTimer >= foodDelay && food.size() < targetFood) {
            food.push_back(generatePosition(snake, food, gridWidth, gridHeight));
            foodTimer = 0.0f;
        }

        BeginDrawing();
        ClearBackground({150, 150, 150, 255});

        for(size_t x = 2; x < gridWidth - 2; x++) {
            for(size_t y = 2; y < gridHeight - 2; y++) {
                Color tileColor = ((x + y) % 2 == 0) ?
                    Color{150, 195, 65, 255} :
                    Color{170, 215, 81, 255};

                DrawRectangle(
                    x * cellSize,
                    y * cellSize,
                    cellSize,
                    cellSize,
                    tileColor
                );
            }
        }

        for(const Position f : food) {
            DrawCircle(
                f.x * cellSize + cellSize / 2,
                f.y * cellSize + cellSize / 2,
                cellSize / 2,
                RED
            );
        }

        for(size_t i = 0; i < snake.size(); i++) {
            int light = 255 - i * ((255 - 75) / snake.size());
            DrawRectangle(
                snake[i].x * cellSize,
                snake[i].y * cellSize,
                cellSize,
                cellSize,
                {0, 121, 241, (unsigned char)light}
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

bool isPositionFree(
    const std::vector<Position> &snake,
    const std::vector<Position> &food,
    Position position
) {
    for(const Position &s : snake) {
        if(s.x == position.x && s.y == position.y) {
            return false;
        }
    }

    for(const Position &f : food) {
        if(f.x == position.x && f.y == position.y) {
            return false;
        }
    }

    return true;
}

Position generatePosition(
    const std::vector<Position> &snake,
    const std::vector<Position> &food,
    int gridWidth,
    int gridHeight
) {
    Position position;

    do {
        position.x = (rand() % (gridWidth - 4)) + 2;
        position.y = (rand() % (gridHeight - 4)) + 2;
    } while(!isPositionFree(snake, food, position));

    return position;
}