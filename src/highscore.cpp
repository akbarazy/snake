#include "../headers/highscore.h"

void HighScore::Save(int score) {
    std::ofstream file("highscore.txt");
    file << score;
}

int HighScore::Load() {
    std::ifstream file("highscore.txt");
    int score = 0;

    if (file.is_open()) file >> score;
    return score;
}