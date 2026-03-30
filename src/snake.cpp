#include "../headers/snake.h"

Snake::Snake() {
    body = { {5, 5}, {4, 5}, {3, 5} };
    direction = RIGHT;
    growNext = false;
}

void Snake::Move() {
    Vector2 head = body[0];

    if (direction == UP) head.y -= 1;
    if (direction == DOWN) head.y += 1;
    if (direction == LEFT) head.x -= 1;
    if (direction == RIGHT) head.x += 1;

    body.insert(body.begin(), head);

    if (!growNext) {
        body.pop_back();
    } else {
        growNext = false;
    }
}

void Snake::Grow() {
    growNext = true;
}

void Snake::Draw() {
    for (auto segment : body) {
        DrawRectangle(segment.x * 20, segment.y * 20, 20, 20, GREEN);
    }
}

void Snake::SetDirection(Direction dir) {
    direction = dir;
}

bool Snake::CheckSelfCollision() {
    Vector2 head = body[0];
    for (int i = 1; i < body.size(); i++) {
        if (body[i].x == head.x && body[i].y == head.y) {
            return true;
        }
    }
    return false;
}

bool Snake::CheckWallCollision(int width, int height) {
    Vector2 head = body[0];
    return (head.x < 0 || head.y < 0 || head.x >= width || head.y >= height);
}

Vector2 Snake::GetHeadPosition() {
    return body[0];
}

std::vector<Vector2> Snake::GetBody() {
    return body;
}