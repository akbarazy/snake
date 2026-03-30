#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"

class Food {
public:
    Vector2 position;

    Food();
    void GeneratePosition();
};

#endif