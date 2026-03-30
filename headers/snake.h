#pragma once
#include "raylib.h"
#include <vector>

class Snake {
private:
    std::vector<Vector2> body;
    Vector2 direction;

public:
    Snake();

    void Move();
    void Grow();
    void Draw();

    void SetDirection(Vector2 dir);
    Vector2 GetHead();

    bool CheckSelfCollision();
    bool CheckWallCollision();
};