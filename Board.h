#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Point.h"

class Board
{
private:
    std::vector<std::string> grid;
    int size=0;
    Point startPos = {0,0};
    Point finishPos = { 0,0 };

public:
    void loadFromFile(const std::string& fileName);
    void print() const;
    bool isInside(int x, int y) const;
    bool isWalkable(int x, int y) const;
    char getCell(int x, int y) const;
    void setCell(int x, int y, char c);
    int getSize() const;
    Point getStartPos() const;
    Point getFinishPos() const;
};