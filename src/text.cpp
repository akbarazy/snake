#include "../headers/text.h"

const int UIStyle::TITLE_SIZE = 50;
const int UIStyle::MENU_SIZE  = 30;
const int UIStyle::TEXT_SIZE  = 20;

const Color UIStyle::PRIMARY = BLUE;
const Color UIStyle::NORMAL  = BLACK;
const Color UIStyle::DANGER  = RED;

int GetCenteredX(const char* text, int fontSize) {
    return (GetScreenWidth() - MeasureText(text, fontSize)) / 2;
}

void DrawCentered(const char* text, int y, int fontSize, Color color) {
    DrawText(text, GetCenteredX(text, fontSize), y, fontSize, color);
}

void DrawTitle(const char* text, int y, Color color) {
    DrawCentered(text, y, UIStyle::TITLE_SIZE, color);
}

void DrawMenu(const char* text, int y, bool selected) {
    DrawCentered(text, y, UIStyle::MENU_SIZE, selected ? UIStyle::PRIMARY : UIStyle::NORMAL);
}

void DrawTextNormal(const std::string& text, int x, int y) {
    DrawText(text.c_str(), x, y, UIStyle::TEXT_SIZE, UIStyle::NORMAL);
}