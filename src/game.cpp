#include "../headers/game.h"
#include <string>

Game::Game() {
    state = MENU;
    difficulty = MEDIUM;
    score = 0;
    menuIndex = 0;

    highScore = HighScore::Load();

    eatSound = LoadSound("assets/eat.wav");
    gameOverSound = LoadSound("assets/gameover.wav");

    SetDifficulty(MEDIUM);
}

void Game::SetDifficulty(Difficulty diff) {
    difficulty = diff;

    if (diff == EASY) moveDelay = 0.2f;
    else if (diff == MEDIUM) moveDelay = 0.12f;
    else moveDelay = 0.08f;
}

void Game::Reset() {
    snake = Snake();
    food.GeneratePosition();
    score = 0;
    moveTimer = 0;
}

void Game::ChangeState(GameState newState) {
    state = newState;
}

void Game::HandleInput() {
    if (state == MENU) {
        if (IsKeyPressed(KEY_DOWN)) menuIndex = (menuIndex + 1) % 2;
        if (IsKeyPressed(KEY_UP)) menuIndex = (menuIndex - 1 + 2) % 2;

        if (IsKeyPressed(KEY_ENTER)) {
            if (menuIndex == 0) {
                Reset();
                ChangeState(PLAYING);
            } else {
                CloseWindow();
            }
        }

        if (IsKeyPressed(KEY_ONE)) SetDifficulty(EASY);
        if (IsKeyPressed(KEY_TWO)) SetDifficulty(MEDIUM);
        if (IsKeyPressed(KEY_THREE)) SetDifficulty(HARD);
    }

    else if (state == PLAYING) {
        if (IsKeyPressed(KEY_P)) ChangeState(PAUSED);

        if (IsKeyPressed(KEY_UP)) snake.SetDirection({0,-1});
        if (IsKeyPressed(KEY_DOWN)) snake.SetDirection({0,1});
        if (IsKeyPressed(KEY_LEFT)) snake.SetDirection({-1,0});
        if (IsKeyPressed(KEY_RIGHT)) snake.SetDirection({1,0});
    }

    else if (state == PAUSED) {
        if (IsKeyPressed(KEY_P)) ChangeState(PLAYING);
    }

    else if (state == GAMEOVER) {
        if (IsKeyPressed(KEY_R)) {
            Reset();
            ChangeState(PLAYING);
        }
        if (IsKeyPressed(KEY_M)) ChangeState(MENU);
    }
}

void Game::Update() {
    if (state != PLAYING) return;

    moveTimer += GetFrameTime();
    if (moveTimer < moveDelay) return;

    moveTimer = 0;
    snake.Move();

    // makan
    if (snake.GetHead().x == food.position.x &&
    snake.GetHead().y == food.position.y) {
        snake.Grow();
        score++;
        PlaySound(eatSound);
        food.GeneratePosition();
    }

    // collision
    if (snake.CheckSelfCollision() || snake.CheckWallCollision()) {
        PlaySound(gameOverSound);
        if (score > highScore) {
            highScore = score;
            HighScore::Save(highScore);
        }
        ChangeState(GAMEOVER);
    }
}

void Game::Draw() {
    if (state == MENU) {
        DrawText("SNAKE GAME", 280, 100, 40, GREEN);

        Color startColor = (menuIndex == 0) ? YELLOW : WHITE;
        Color exitColor = (menuIndex == 1) ? YELLOW : WHITE;

        DrawText("Start Game", 320, 250, 30, startColor);
        DrawText("Exit", 350, 300, 30, exitColor);

        DrawText("1: Easy  2: Medium  3: Hard", 230, 400, 20, GRAY);

        std::string diffText;

        if (difficulty == EASY) diffText = "Difficulty: EASY";
        else if (difficulty == MEDIUM) diffText = "Difficulty: MEDIUM";
        else diffText = "Difficulty: HARD";

        DrawText(diffText.c_str(), 280, 450, 20, GREEN);
    }

    else if (state == PLAYING || state == PAUSED) {
        snake.Draw();
        food.Draw();

        DrawText(("Score: " + std::to_string(score)).c_str(), 10, 10, 20, WHITE);
        DrawText(("High: " + std::to_string(highScore)).c_str(), 10, 40, 20, GRAY);

        if (state == PAUSED)
            DrawText("PAUSED (P to resume)", 250, 300, 30, YELLOW);
    }

    else if (state == GAMEOVER) {
        DrawText("GAME OVER", 280, 200, 40, RED);
        DrawText(("Score: " + std::to_string(score)).c_str(), 300, 260, 25, WHITE);
        DrawText("R: Restart  M: Menu", 260, 320, 20, GRAY);
    }
}