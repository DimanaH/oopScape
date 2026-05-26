#pragma once
#include "Point.h"
#include "Board.h"

class Enemy
{
protected:
    Point pos;

public:
    Enemy(Point startPos);
    virtual ~Enemy() = default;

    virtual char getSymbol() const = 0;
    virtual std::string getType() const = 0;
    virtual void move(const Point& heroPos, const Board& board, bool heroInvisible) = 0;

    Point getPos() const;
};