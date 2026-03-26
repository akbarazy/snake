#include "../headers/food.h"
#include "raylib.h"
#include <cstdlib>

bool isFree(const std::vector<Position>& snake, Position p) {
    for(const auto& s : snake) {
        if(s.x == p.x && s.y == p.y) return false;
    }
    return true;
}

void Food::Spawn(const std::vector<Position>& snake, int gridW, int gridH) {
    while(true) {
        Position p = {
            rand() % (gridW - 4) + 2,
            rand() % (gridH - 4) + 2
        };

        if(isFree(snake, p)) {
            pos = p;
            break;
        }
    }
}

void Food::Draw(int cellSize) {
    DrawCircle(
        pos.x * cellSize + cellSize/2,
        pos.y * cellSize + cellSize/2,
        cellSize/2,
        RED
    );
}

Position Food::GetPosition() {
    return pos;
}