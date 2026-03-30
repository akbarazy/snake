#include "../headers/food.h"

Food::Food() {
    position = {10, 10};
}

void Food::GeneratePosition(int width, int height) {
    position.x = GetRandomValue(0, width - 1);
    position.y = GetRandomValue(0, height - 1);
}

void Food::Draw() {
    DrawRectangle(position.x * 20, position.y * 20, 20, 20, RED);
}

Vector2 Food::GetPosition() {
    return position;
}