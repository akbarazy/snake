#include "../headers/food.h"

bool IsOnSnake(Vector2 newPosition, const Snake &snake) {
    for (auto &position : snake.GetBody()) {
        if (position.x == newPosition.x && position.y == newPosition.y)
            return true;
    }
    return false;
}

bool IsOnFoods(Vector2 newPosition, const std::vector<Food> &foods) {
    for (auto &food : foods) {
        if (food.position.x == newPosition.x && food.position.y == newPosition.y)
            return true;
    }
    return false;
}

Food::Food(Vector2 newPosition) {
    position = newPosition;
}

void Food::GeneratePosition(const Snake &snake, const std::vector<Food> &foods) {
    std::vector<Vector2> freePositions;

    for (int x = 0; x < 35; x++) {
        for (int y = 0; y < 35; y++) {
            Vector2 newPosition = {(float)x, (float)y};

            if (!IsOnSnake(newPosition, snake) && !IsOnFoods(newPosition, foods)) {
                freePositions.push_back(newPosition);
            }
        }
    }

    if (!freePositions.empty()) {
        int index = GetRandomValue(0, freePositions.size() - 1);
        position = freePositions[index];
    }
}

void Food::Draw() {
    DrawCircle(position.x * 20 + 30, position.y * 20 + 50, 10, RED);
}