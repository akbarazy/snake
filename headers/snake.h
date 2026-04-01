#pragma once
#include "raylib.h"
#include <vector>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
private:
    std::vector<Vector2> body;
    Direction direction;
    Direction prevDirection;

public:
    Snake();
    void Move();
    void Grow();
    void Draw();
    void SetDirection(Direction newDirection);
    Direction GetPrevDirection();
    Vector2 GetHead();
    bool IsChangeDirection();
    bool IsSelfCollision();
    bool IsWallCollision();
};