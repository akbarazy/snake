#pragma once
#include "raylib.h"

class Food {
public:
    Vector2 position;

    void GeneratePosition();
    void Draw();
};