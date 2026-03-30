#pragma once
#include <fstream>

class HighScore {
public:
    static void Save(int score);
    static int Load();
};