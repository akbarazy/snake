#include "../headers/food.h"

void Food::GeneratePosition() {
    position = {
        (float)GetRandomValue(0, 39),
        (float)GetRandomValue(0, 29)
    };
}

void Food::Draw() {
    DrawRectangle(position.x * 20, position.y * 20, 20, 20, RED);
}