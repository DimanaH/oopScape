#pragma once
#include <vector>
#include <string>

#include "Point.h"

class Board
{
private:
    std::vector<std::string> grid;
    size_t size;

    Point startPos;
    Point finishPos;

public:
    bool loadFromFile(const std::string& fileName);

    void print() const;


    bool isWalkable(int x, int y) const;

    char getCell(int x, int y) const;

    size_t getSize() const;

    Point getStartPos() const;

    Point getFinishPos() const;
};