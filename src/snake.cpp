#include "../headers/snake.h"

Snake::Snake() {
    body = {{10,10}, {9,10}, {8,10}};
    direction = {1,0};
}

void Snake::Move() {
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i-1];
    }
    body[0].x += direction.x;
    body[0].y += direction.y;
}

void Snake::Grow() {
    body.push_back(body.back());
}

void Snake::Draw() {
    for (auto &part : body) {
        DrawRectangle(part.x * 20, part.y * 20, 20, 20, GREEN);
    }
}

void Snake::SetDirection(Vector2 dir) {
    direction = dir;
}

Vector2 Snake::GetHead() {
    return body[0];
}

bool Snake::CheckSelfCollision() {
    for (int i = 1; i < body.size(); i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
            return true;
    }
    return false;
}

bool Snake::CheckWallCollision() {
    return (body[0].x < 0 || body[0].x >= 40 || body[0].y < 0 || body[0].y >= 30);
}