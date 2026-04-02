#pragma once
#include "raylib.h"

class Food {
public:
    Vector2 position;
    Food(Vector2 newPosition);
    void GeneratePosition();
    void Draw();
};