#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "raylib.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    std::vector<Vector2> body;
    Direction direction;
    bool shouldGrow;

    Snake();

    void Move();
    void Grow();
    bool CheckSelfCollision();
    void Reset();
};

#endif