#pragma once
#include "raylib.h"
#include "snake.h"

class Food {
public:
    Vector2 position;
    Food(Vector2 newPosition);
    void GeneratePosition(const Snake &snake, const std::vector<Food> &foods);
    void Draw();
};