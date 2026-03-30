#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "raylib.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    std::vector<Vector2> body;
    Direction direction;
    bool growNext;

public:
    Snake();

    void Move();
    void Grow();
    void Draw();
    void SetDirection(Direction dir);
    bool CheckSelfCollision();
    bool CheckWallCollision(int width, int height);
    Vector2 GetHeadPosition();
    std::vector<Vector2> GetBody();
};

#endif