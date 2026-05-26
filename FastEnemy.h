#pragma once
#include "Enemy.h"

class FastEnemy : public Enemy
{
public:
    FastEnemy(Point startPos);
    char getSymbol() const override;
    std::string getType() const override;
    void move(const Point& heroPos, const Board& board, bool heroInvisible) override;
};