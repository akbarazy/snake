#pragma once
#include <vector>

struct Position { int x, y; };
enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    std::vector<Position> body;
    Direction currentDir;
    Direction prevDir;
    bool grow;

public:
    Snake();

    void HandleInput();
    void Update();
    void Draw(int cellSize);

    void Grow();
    bool CheckSelfCollision();
    Position GetHead();
    const std::vector<Position>& GetBody();
};