#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"

class Game {
private:
    Snake snake;
    Food food;
    int score;
    bool gameOver;
    float timer;

    const int gridWidth = 30;
    const int gridHeight = 30;

public:
    Game();

    void Update();
    void Draw();
    void Reset();
};

#endif