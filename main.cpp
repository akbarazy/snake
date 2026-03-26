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
    int screenHeight = 620;

    int gridWidth = screenWidth / cellSize;
    int gridHeight = screenHeight / cellSize;

    int framesRate = 60;
    int framesCounter = 0;
    int snakeSpeed = framesRate / 5;

    int totalCells = (gridWidth - 4) * (gridHeight - 4);
    bool grow = false;
    bool gameOver = false;

    std::vector<Position> snake = {
        {15, 15}, {14, 15}, {13, 15}, {12, 15}, {11, 15}
    };

    std::vector<Position> food = {
        {24, 15}, {27, 12}, {21, 12}, {27, 18}, {21, 18}
    };

    Position head = snake[0];
    Position leftEye = {10, 3};
    Position rightEye = {10, 12};

    Direction prevDir = RIGHT;
    Direction currentDir = RIGHT;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(framesRate);
    srand(time(0));

    while(!WindowShouldClose()) {
        if(!gameOver) {
            if(IsKeyPressed(KEY_UP) && prevDir != DOWN) currentDir = UP;
            if(IsKeyPressed(KEY_DOWN) && prevDir != UP) currentDir = DOWN;
            if(IsKeyPressed(KEY_LEFT) && prevDir != RIGHT) currentDir = LEFT;
            if(IsKeyPressed(KEY_RIGHT) && prevDir != LEFT) currentDir = RIGHT;

            if(framesCounter >= snakeSpeed) {
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

                if(
                    head.x < 2 || head.x >= (gridWidth - 2) ||
                    head.y < 2 || head.y >= (gridHeight - 2)
                ) gameOver = true;

                for(size_t i = 1; i < snake.size(); i++) {
                    if(head.x == snake[i].x && head.y == snake[i].y) {
                        gameOver = true;
                        break;
                    }
                }

                snake.insert(snake.begin(), head);

                for(size_t i = 0; i < food.size(); i++) {
                    if(head.x == food[i].x && head.y == food[i].y) {
                        grow = true;
                        food.erase(food.begin() + i);

                        if(snake.size() < totalCells) {
                            Position newFood = generatePosition(snake, food, gridWidth, gridHeight);
                            if(newFood.x != -1 && newFood.y != -1) food.push_back(newFood);
                        }
                        break;
                    }
                }

                if(!grow) {
                    snake.pop_back();
                }

                grow = false;
                prevDir = currentDir;
                framesCounter = 0;
            } else {
                framesCounter++;
            }
        }

        BeginDrawing();
        ClearBackground({150, 150, 150, 255});

        for(int x = 2; x < gridWidth - 2; x++) {
            for(int y = 2; y < gridHeight - 2; y++) {
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

        for(const Position &f : food) {
            DrawCircle(
                f.x * cellSize + cellSize / 2,
                f.y * cellSize + cellSize / 2,
                cellSize / 2,
                RED
            );
        }

        for(int i = snake.size() - 1; i >= 0; i--) {
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

        if(gameOver) {
            DrawRectangle(
                screenWidth / 2 - 100, 
                screenHeight / 2 - 17, 
                200, 40,
                {150, 150, 150, 255}
            );
            DrawText(
                "GAME OVER", 
                screenWidth / 2 - 91, 
                screenHeight / 2 - 10, 
                30, RED
            );
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
        if(s.x == position.x && s.y == position.y) return false;
    }

    for(const Position &f : food) {
        if(f.x == position.x && f.y == position.y) return false;
    }

    return true;
}

Position generatePosition(
    const std::vector<Position> &snake,
    const std::vector<Position> &food,
    int gridWidth,
    int gridHeight
) {
    std::vector<Position> freePositions;

    for(int x = 2; x < gridWidth - 2; x++) {
        for(int y = 2; y < gridHeight - 2; y++) {
            Position pos = {x, y};
            if(isPositionFree(snake, food, pos)) {
                freePositions.push_back(pos);
            }
        }
    }

    if(freePositions.empty()) return {-1, -1};

    int index = rand() % freePositions.size();
    return freePositions[index];
}