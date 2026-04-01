#include "../headers/snake.h"

Snake::Snake() {
    body = {{10,10}, {9,10}, {8,10}};
    direction = prevDirection = RIGHT;
}

void Snake::Move() {
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i-1];
    }

    switch (direction) {
        case UP: 
            body[0].y--;
            break;
        case DOWN: 
            body[0].y++;
            break;
        case LEFT: 
            body[0].x--;
            break;
        case RIGHT: 
            body[0].x++;
            break;
    }

    prevDirection = direction;
}

void Snake::Grow() {
    body.push_back(body.back());
}

void Snake::Draw() {
    for (int i = body.size() - 1; i >= 0; i--) {
        int light = 255 - i * ((255 - 75) / body.size());
        DrawRectangle(body[i].x * 20, body[i].y * 20, 20, 20, {0, 121, 241, (unsigned char)light});
    }
}

void Snake::SetDirection(Direction newDirection) {
    direction = newDirection;
}

Direction Snake::GetPrevDirection() {
    return prevDirection;
}

Vector2 Snake::GetHead() {
    return body[0];
}

bool Snake::IsSelfCollision() {
    for (int i = 1; i < body.size(); i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
            return true;
    }

    return false;
}

bool Snake::IsWallCollision() {
    return (body[0].x < 0 || body[0].x >= 35 || body[0].y < 0 || body[0].y >= 35);
}