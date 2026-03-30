#include "../headers/game.h"

const int CELL_SIZE = 25;
const int GRID_SIZE = 20;

Game::Game() {
    // InitAudioDevice();

    // eatSound = LoadSound("assets/eat.wav");
    // gameOverSound = LoadSound("assets/gameover.wav");

    moveDelay = 0.15f;
    moveTimer = 0.0f;

    Reset();
}

void Game::Reset() {
    snake.Reset();
    food.GeneratePosition();
    score = 0;
    state = PLAYING;
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_P)) {
        if (state == PLAYING) state = PAUSED;
        else if (state == PAUSED) state = PLAYING;
    }

    if (IsKeyPressed(KEY_R) && state == GAME_OVER) {
        Reset();
    }

    if (state != PLAYING) return;

    if (IsKeyPressed(KEY_UP) && snake.direction != DOWN) snake.direction = UP;
    if (IsKeyPressed(KEY_DOWN) && snake.direction != UP) snake.direction = DOWN;
    if (IsKeyPressed(KEY_LEFT) && snake.direction != RIGHT) snake.direction = LEFT;
    if (IsKeyPressed(KEY_RIGHT) && snake.direction != LEFT) snake.direction = RIGHT;
}

void Game::Update() {
    if (state != PLAYING) return;

    moveTimer += GetFrameTime();

    if (moveTimer >= moveDelay) {
        moveTimer = 0.0f;

        snake.Move();

        // Collision with wall
        Vector2 head = snake.body[0];
        if (head.x < 0 || head.x >= GRID_SIZE || head.y < 0 || head.y >= GRID_SIZE) {
            state = GAME_OVER;
            // PlaySound(gameOverSound);
        }

        // Self collision
        if (snake.CheckSelfCollision()) {
            state = GAME_OVER;
            // PlaySound(gameOverSound);
        }

        // Eat food
        if (head.x == food.position.x && head.y == food.position.y) {
            snake.Grow();
            food.GeneratePosition();
            score += 10;
            // PlaySound(eatSound);
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw snake
    for (auto segment : snake.body) {
        DrawRectangle(segment.x * CELL_SIZE, segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
    }

    // Draw food
    DrawRectangle(food.position.x * CELL_SIZE, food.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    // UI Score
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

    // Pause
    if (state == PAUSED) {
        DrawText("PAUSED", 200, 200, 40, YELLOW);
    }

    // Game Over UI
    if (state == GAME_OVER) {
        DrawText("GAME OVER", 180, 180, 40, RED);
        DrawText("Press R to Restart", 150, 230, 20, WHITE);
    }

    EndDrawing();
}