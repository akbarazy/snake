#include "../headers/game.h"
#include "raylib.h"

Game::Game(int screenW, int screenH, int cell) {
    cellSize = cell;
    gridW = screenW / cell;
    gridH = screenH / cell;

    frameCounter = 0;
    speed = 12;
    gameOver = false;

    food.Spawn(snake.GetBody(), gridW, gridH);
}

void Game::Update() {
    if(gameOver) return;

    snake.HandleInput();

    if(frameCounter >= speed) {
        snake.Update();

        Position head = snake.GetHead();

        if(head.x < 2 || head.x >= gridW-2 || head.y < 2 || head.y >= gridH-2)
            gameOver = true;

        if(snake.CheckSelfCollision())
            gameOver = true;

        if(head.x == food.GetPosition().x && head.y == food.GetPosition().y) {
            snake.Grow();
            food.Spawn(snake.GetBody(), gridW, gridH);
        }

        frameCounter = 0;
    } else {
        frameCounter++;
    }
}

void Game::Draw() {
    ClearBackground({150,150,150,255});

    for(int x=2; x<gridW-2; x++) {
        for(int y=2; y<gridH-2; y++) {
            Color c = ((x+y)%2==0) ?
                Color{150,195,65,255} :
                Color{170,215,81,255};

            DrawRectangle(x*cellSize,y*cellSize,cellSize,cellSize,c);
        }
    }

    snake.Draw(cellSize);
    food.Draw(cellSize);

    if(gameOver) {
        DrawText("GAME OVER", 300, 300, 30, RED);
    }
}

bool Game::IsGameOver() {
    return gameOver;
}