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
    std::vector<Food> foods;
    GameState gameState;
    Difficulty difficulty;
    int maxFood;
    int score;
    int highScore;
    float moveTimer;
    float moveDelay;
    int menuIndex;
    Sound menuSound;
    Sound turnSound;
    Sound eatSound;
    Sound gameOverSound;

public:
    Game();
    void HandleInput();
    void Update();
    void Draw();
    void Reset();
    void setGameState(GameState newGameState);
    void SetDifficulty(Difficulty newDifficulty);
};