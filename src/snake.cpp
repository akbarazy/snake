#include "../headers/snake.h"

Snake::Snake() {
    body = {{12, 17}, {11, 17}, {10, 17}, {9, 17}, {8, 17}};
    leftEye = {10, 3};
    rightEye = {10, 13};
    direction = prevDirection = RIGHT;
}

void Snake::Move() {
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i-1];
    }

    switch (direction) {
        case UP: 
            body[0].y--;
            leftEye = {3, 5};
            rightEye = {13, 5};
            break;

        case DOWN: 
            body[0].y++;
            leftEye = {3, 10};
            rightEye = {13, 10};
            break;

        case LEFT: 
            body[0].x--;
            leftEye = {5, 3};
            rightEye = {5, 13};
            break;

        case RIGHT: 
            body[0].x++;
            leftEye = {10, 3};
            rightEye = {10, 13};
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
        DrawRectangle(body[i].x * 20 + 20, body[i].y * 20 + 40, 20, 20, {0, 121, 241, (unsigned char)light});
    
        if(i == 0) {
            DrawRectangle(body[0].x * 20 + 20 + leftEye.x, body[0].y * 20  + 40 + leftEye.y, 4, 4, RAYWHITE);
            DrawRectangle( body[0].x * 20 + 20 + rightEye.x, body[0].y * 20  + 40 + rightEye.y, 4, 4, RAYWHITE);
        }
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

const std::vector<Vector2>& Snake::GetBody() const {
    return body;
}

bool Snake::IsChangeDirection() {
    if (direction != prevDirection) return true;
    return false;
}

bool Snake::IsSelfCollision() {
    for (size_t i = 1; i < body.size(); i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
            return true;
    }
    return false;
}

bool Snake::IsWallCollision() {
    return (body[0].x < 0 || body[0].x >= 35 || body[0].y < 0 || body[0].y >= 35);
}