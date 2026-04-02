#include "../headers/game.h"
#include <string>

Game::Game() {
    gameState = MENU;
    SetDifficulty(MEDIUM);
    maxFood = 5;
    score = 0;
    menuIndex = 0;
    highScore = HighScore::Load();
    menuSound = LoadSound("assets/button.wav");
    turnSound = LoadSound("assets/turn.wav");
    eatSound = LoadSound("assets/eat.wav");
    gameOverSound = LoadSound("assets/gameover.wav");
}

void Game::SetDifficulty(Difficulty newDifficulty) {
    difficulty = newDifficulty;

    if (newDifficulty == EASY) moveDelay = 0.2f;
    else if (newDifficulty == MEDIUM) moveDelay = 0.12f;
    else moveDelay = 0.08f;
}

void Game::Reset() {
    snake = Snake();
    foods.clear();
    foods = {
        Food({24, 18}),
        Food({21, 15}),
        Food({27, 15}),
        Food({21, 21}),
        Food({27, 21})
    };
    score = 0;
    moveTimer = 0;
}

void Game::setGameState(GameState newGameState) {
    gameState = newGameState;
}

void Game::HandleInput() {
    if (gameState == MENU) {
        if (IsKeyPressed(KEY_DOWN)) menuIndex = (menuIndex + 1) % 2;
        if (IsKeyPressed(KEY_UP)) menuIndex = (menuIndex - 1 + 2) % 2;

        if (IsKeyPressed(KEY_ENTER)) {
            if (menuIndex == 0) {
                Reset();
                setGameState(PLAYING);
            } else {
                CloseWindow();
            }
        }

        if (IsKeyPressed(KEY_ONE)) SetDifficulty(EASY);
        if (IsKeyPressed(KEY_TWO)) SetDifficulty(MEDIUM);
        if (IsKeyPressed(KEY_THREE)) SetDifficulty(HARD);

        if (
            IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||
            IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ONE) ||
            IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_THREE)
        ) PlaySound(menuSound);
    }

    else if (gameState == PLAYING) {
        if (IsKeyPressed(KEY_P)) {
            setGameState(PAUSED);
            PlaySound(menuSound);
        }

        if (IsKeyPressed(KEY_UP) && snake.GetPrevDirection() != DOWN) snake.SetDirection(UP);
        if (IsKeyPressed(KEY_DOWN) && snake.GetPrevDirection() != UP) snake.SetDirection(DOWN);
        if (IsKeyPressed(KEY_LEFT) && snake.GetPrevDirection() != RIGHT) snake.SetDirection(LEFT);
        if (IsKeyPressed(KEY_RIGHT) && snake.GetPrevDirection() != LEFT) snake.SetDirection(RIGHT);
    }

    else if (gameState == PAUSED) {
        if (IsKeyPressed(KEY_P)) {
            setGameState(PLAYING);
            PlaySound(menuSound);
        }
    }

    else if (gameState == GAMEOVER) {
        if (IsKeyPressed(KEY_R)) {
            Reset();
            setGameState(PLAYING);
        }
        if (IsKeyPressed(KEY_M)) setGameState(MENU);

        if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_M)) 
            PlaySound(menuSound);
    }
}

void Game::Update() {
    if (gameState != PLAYING) return;

    moveTimer += GetFrameTime();
    if (moveTimer < moveDelay) return;

    if (snake.IsChangeDirection()) PlaySound(turnSound);
    moveTimer = 0;
    snake.Move();

    for (auto &food : foods) {
        if (
            snake.GetHead().x == food.position.x &&
            snake.GetHead().y == food.position.y
        ) {
            snake.Grow();
            score++;
            PlaySound(eatSound);
            food.GeneratePosition();
        }

        if (snake.IsSelfCollision() || snake.IsWallCollision()) {
            PlaySound(gameOverSound);
            if (score > highScore) {
                highScore = score;
                HighScore::Save(highScore);
            }
            setGameState(GAMEOVER);
        }
    }
}

void Game::Draw() {
    if (gameState == MENU) {
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

    else if (gameState == PLAYING || gameState == PAUSED) {
        for(int x = 0; x < 35; x++) {
            for(int y = 0; y < 35; y++) {
                Color tileColor = ((x + y) % 2 == 0) ?
                    Color{150, 195, 65, 255} :
                    Color{170, 215, 81, 255};

                DrawRectangle(
                    x * 20 + 20, y * 20 + 40,
                    20, 20, tileColor
                );
            }
        }

        snake.Draw();
        for (auto &food : foods) {
            food.Draw();
        }

        DrawText(("Score: " + std::to_string(score)).c_str(), 20, 10, 20, WHITE);
        DrawText(("High: " + std::to_string(highScore)).c_str(), 140, 10, 20, GRAY);

        if (gameState == PAUSED)
            DrawText("PAUSED (P to resume)", 250, 300, 30, YELLOW);
    }

    else if (gameState == GAMEOVER) {
        DrawText("GAME OVER", 280, 200, 40, RED);
        DrawText(("Score: " + std::to_string(score)).c_str(), 300, 260, 25, WHITE);
        DrawText("R: Restart  M: Menu", 260, 320, 20, GRAY);
    }
}