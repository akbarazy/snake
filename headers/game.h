#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "raylib.h"

enum GameState { PLAYING, PAUSED, GAME_OVER };

class Game {
public:
    Snake snake;
    Food food;

    int score;
    GameState state;

    // Sound eatSound;
    // Sound gameOverSound;

    float moveTimer;
    float moveDelay;

    Game();

    void Update();
    void Draw();
    void HandleInput();
    void Reset();
};

#endif