#include "../headers/snake.h"

Snake::Snake() {
    Reset();
}

void Snake::Reset() {
    body = { {10, 10}, {9, 10}, {8, 10} };
    direction = RIGHT;
    shouldGrow = false;
}

void Snake::Move() {
    Vector2 head = body[0];

    switch (direction) {
        case UP: head.y -= 1; break;
        case DOWN: head.y += 1; break;
        case LEFT: head.x -= 1; break;
        case RIGHT: head.x += 1; break;
    }

    body.insert(body.begin(), head);

    if (!shouldGrow) {
        body.pop_back();
    } else {
        shouldGrow = false;
    }
}

void Snake::Grow() {
    shouldGrow = true;
}

bool Snake::CheckSelfCollision() {
    for (size_t i = 1; i < body.size(); i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            return true;
        }
    }
    return false;
}