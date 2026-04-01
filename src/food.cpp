#include "../headers/food.h"

void Food::GeneratePosition() {
    position = {
        (float)GetRandomValue(0, 34),
        (float)GetRandomValue(0, 34)
    };
}

void Food::Draw() {
    DrawCircle(position.x * 20 + 10, position.y * 20 + 10, 10, RED);
}