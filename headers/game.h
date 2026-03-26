#pragma once
#include "snake.h"
#include "food.h"

class Game {
private:
    Snake snake;
    Food food;

    int gridW, gridH;
    int cellSize;

    int frameCounter;
    int speed;
    bool gameOver;

public:
    Game(int screenW, int screenH, int cell);

    void Update();
    void Draw();

    bool IsGameOver();
};