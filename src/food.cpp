#include "../headers/food.h"

Food::Food() {
    GeneratePosition();
}

void Food::GeneratePosition() {
    position = {
        (float)GetRandomValue(0, 19),
        (float)GetRandomValue(0, 19)
    };
}