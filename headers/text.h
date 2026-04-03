#pragma once
#include "raylib.h"
#include <string>

namespace UIStyle {
    extern const int TITLE_SIZE;
    extern const int MENU_SIZE;
    extern const int TEXT_SIZE;

    extern const Color PRIMARY;
    extern const Color NORMAL;
    extern const Color DANGER;
}

int GetCenteredX(const char* text, int fontSize);
void DrawCentered(const char* text, int y, int fontSize, Color color);

void DrawTitle(const char* text, int y, Color color);
void DrawMenu(const char* text, int y, bool selected);
void DrawTextNormal(const std::string& text, int x, int y);