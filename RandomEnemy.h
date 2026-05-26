#pragma once
#include "Enemy.h"

class RandomEnemy : public Enemy
{
public:
    RandomEnemy(Point startPos);
    char getSymbol() const override;
    std::string getType() const override;
    void move(const Point& heroPos, const Board& board, bool heroInvisible) override;
};