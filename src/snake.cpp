#include "../headers/snake.h"
#include "raylib.h"

Snake::Snake() {
    body = {{15,15},{14,15},{13,15},{12,15},{11,15}};
    currentDir = RIGHT;
    prevDir = RIGHT;
    grow = false;
}

void Snake::HandleInput() {
    if(IsKeyPressed(KEY_UP) && prevDir != DOWN) currentDir = UP;
    if(IsKeyPressed(KEY_DOWN) && prevDir != UP) currentDir = DOWN;
    if(IsKeyPressed(KEY_LEFT) && prevDir != RIGHT) currentDir = LEFT;
    if(IsKeyPressed(KEY_RIGHT) && prevDir != LEFT) currentDir = RIGHT;
}

void Snake::Update() {
    Position head = body[0];

    switch(currentDir) {
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
    }

    body.insert(body.begin(), head);

    if(!grow) body.pop_back();
    grow = false;

    prevDir = currentDir;
}

void Snake::Draw(int cellSize) {
    for(int i = body.size() - 1; i >= 0; i--) {
        DrawRectangle(
            body[i].x * cellSize,
            body[i].y * cellSize,
            cellSize,
            cellSize,
            BLUE
        );
    }
}

void Snake::Grow() {
    grow = true;
}

bool Snake::CheckSelfCollision() {
    Position head = body[0];
    for(size_t i = 1; i < body.size(); i++) {
        if(head.x == body[i].x && head.y == body[i].y) return true;
    }
    return false;
}

Position Snake::GetHead() {
    return body[0];
}

const std::vector<Position>& Snake::GetBody() {
    return body;
}