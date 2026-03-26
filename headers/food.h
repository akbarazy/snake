#pragma once
#include <vector>
#include "snake.h"

class Food {
private:
    Position pos;

public:
    void Spawn(const std::vector<Position>& snake, int gridW, int gridH);
    void Draw(int cellSize);
    Position GetPosition();
};