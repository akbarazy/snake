#include "../headers/game.h"
#include "raylib.h"

Game::Game() {
    Reset();
}

void Game::Reset() {
    snake = Snake();
    food.GeneratePosition(gridWidth, gridHeight);
    score = 0;
    gameOver = false;
    timer = 0;
}

void Game::Update() {
    if (gameOver) {
        if (IsKeyPressed(KEY_R)) {
            Reset();
        }
        return;
    }

    // Input
    if (IsKeyPressed(KEY_UP)) snake.SetDirection(UP);
    if (IsKeyPressed(KEY_DOWN)) snake.SetDirection(DOWN);
    if (IsKeyPressed(KEY_LEFT)) snake.SetDirection(LEFT);
    if (IsKeyPressed(KEY_RIGHT)) snake.SetDirection(RIGHT);

    // Movement timing (biar tidak terlalu cepat)
    timer += GetFrameTime();
    if (timer >= 0.15f) {
        snake.Move();
        timer = 0;

        // Makan makanan
        if (snake.GetHeadPosition().x == food.GetPosition().x &&
            snake.GetHeadPosition().y == food.GetPosition().y) {
            snake.Grow();
            food.GeneratePosition(gridWidth, gridHeight);
            score++;
        }

        // Collision
        if (snake.CheckSelfCollision() || snake.CheckWallCollision(gridWidth, gridHeight)) {
            gameOver = true;
        }
    }
}

void Game::Draw() {
    snake.Draw();
    food.Draw();

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

    if (gameOver) {
        DrawText("GAME OVER", 200, 250, 30, RED);
        DrawText("Press R to Restart", 180, 300, 20, WHITE);
    }
}