#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"

class Food {
private:
    Vector2 position;

public:
    Food();

    void GeneratePosition(int width, int height);
    void Draw();
    Vector2 GetPosition();
};

#endif