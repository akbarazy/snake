#pragma once
#include "snake.h"
#include "food.h"
#include "highscore.h"
#include "raylib.h"

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAMEOVER
};

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

class Game {
private:
    Snake snake;
    Food food;

    GameState state;
    Difficulty difficulty;

    int score;
    int highScore;

    float moveTimer;
    float moveDelay;

    int menuIndex;

    Sound eatSound;
    Sound gameOverSound;

public:
    Game();

    void HandleInput();
    void Update();
    void Draw();

    void Reset();
    void ChangeState(GameState newState);
    void SetDifficulty(Difficulty diff);
};