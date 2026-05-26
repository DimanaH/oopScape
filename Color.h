#pragma once
#include <windows.h>
#include <iostream>
#include <string>

enum class Color {
    White = 7,
    Cyan = 11,
    Red = 12,
    Yellow = 14,
    Gray = 8
};

inline void setColor(Color c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)c);
}

inline void resetColor()
{
    setColor(Color::White);
}

inline void printColored(const std::string& text, Color c)
{
    setColor(c);
    std::cout << text;
    resetColor();
}