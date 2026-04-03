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
        Food({24, 17}),
        Food({21, 14}),
        Food({27, 14}),
        Food({21, 20}),
        Food({27, 20})
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
        if (IsKeyPressed(KEY_RIGHT)) menuIndex = (menuIndex + 1) % 2;
        if (IsKeyPressed(KEY_LEFT)) menuIndex = (menuIndex - 1 + 2) % 2;

        if (IsKeyPressed(KEY_ENTER)) {
            if (menuIndex == 0) {
                Reset();
                setGameState(PLAYING);
            } else {
                setGameState(MENU);
            }
        }

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_ENTER)) 
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
            food.GeneratePosition(snake, foods);
        }

        if (snake.IsSelfCollision() || snake.IsWallCollision()) {
            PlaySound(gameOverSound);
            if (score > highScore) {
                highScore = score;
                HighScore::Save(highScore);
            }
            setGameState(GAMEOVER);
            menuIndex = 0;
        }
    }
}

void Game::Draw() {
    if (gameState == MENU) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        int titleSize = 50;
        int activeSize = 30;
        int normalSize = 20;
        int menuSize = 30;

        int spacing = 35;

        int totalHeight =
            titleSize +
            spacing +
            activeSize +
            spacing +
            menuSize +
            10 +
            menuSize;

        int startY = (screenHeight - totalHeight) / 2 - 35;

        const char* title = "SNAKE GAME";
        int titleWidth = MeasureText(title, titleSize);

        DrawText(title,
                (screenWidth - titleWidth) / 2,
                startY,
                titleSize,
                BLUE);

        int centerX = screenWidth / 2;
        int diffY = startY + titleSize + spacing;

        const char *activeText;
        const char *leftText;
        const char *rightText;

        switch (difficulty) {
            case EASY:
                activeText = "EASY";
                leftText   = "HARD";
                rightText  = "MEDIUM";
                break;
            case MEDIUM:
                activeText = "MEDIUM";
                leftText   = "EASY";
                rightText  = "HARD";
                break;
            case HARD:
                activeText = "HARD";
                leftText   = "MEDIUM";
                rightText  = "EASY";
                break;
        }

        int activeWidth = MeasureText(activeText, activeSize);
        int leftWidth   = MeasureText(leftText, normalSize);

        DrawText(activeText,
                centerX - activeWidth / 2,
                diffY,
                activeSize,
                BLUE);

        DrawText(leftText,
                centerX - activeWidth / 2 - leftWidth - 20,
                diffY + (activeSize - normalSize) / 2,
                normalSize,
                BLACK);

        DrawText(rightText,
                centerX + activeWidth / 2 + 20,
                diffY + (activeSize - normalSize) / 2,
                normalSize,
                BLACK);

        int menuY = diffY + activeSize + spacing;

        const char* startText = "Start Game";
        int startWidth = MeasureText(startText, menuSize);
        Color startColor = (menuIndex == 0) ? BLUE : BLACK;

        DrawText(startText,
                (screenWidth - startWidth) / 2,
                menuY,
                menuSize,
                startColor);

        const char* exitText = "Exit";
        int exitWidth = MeasureText(exitText, menuSize);
        Color exitColor = (menuIndex == 1) ? BLUE : BLACK;

        DrawText(exitText,
                (screenWidth - exitWidth) / 2,
                menuY + menuSize + 10,
                menuSize,
                exitColor);
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

        DrawText(("Score: " + std::to_string(score)).c_str(), 20, 10, 20, BLACK);
        DrawText(("High: " + std::to_string(highScore)).c_str(), 140, 10, 20, BLACK);

        if (gameState == PAUSED) {
            int positionX = (GetScreenWidth() - MeasureText("PAUSED", 50)) / 2;
            int positionY = (GetScreenHeight() - 50) / 2 - 20;
            DrawRectangle(positionX - 10, positionY - 7, MeasureText("PAUSED", 50) + 20, 60, LIGHTGRAY);
            DrawText("PAUSED", positionX, positionY, 50, BLACK);
        }
    }

    else if (gameState == GAMEOVER) {
        int startY = (GetScreenHeight() - 50 - 60 - 70) / 2 - 15;
        int positionX = (GetScreenWidth() - MeasureText("GAME OVER", 50)) / 2;
        DrawText("GAME OVER", positionX, startY, 50, RED);
        
        positionX = (GetScreenWidth() - MeasureText(("Score: " + std::to_string(score)).c_str(), 30)) / 2;
        DrawText(("Score: " + std::to_string(score)).c_str(), positionX, startY + 75, 30, BLACK);

        positionX = (GetScreenWidth() - MeasureText("Restart", 30)) / 2;
        DrawText("Restart", positionX - 51, startY + 130, 30, menuIndex == 0 ? BLUE : BLACK);

        positionX = (GetScreenWidth() - MeasureText("Menu", 30)) / 2;
        DrawText("Menu", positionX + 74, startY + 130, 30, menuIndex == 1 ? BLUE : BLACK);
    }
}