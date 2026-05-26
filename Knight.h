#pragma once
#include "Hero.h"

class Knight : public Hero
{
public:
    Knight(Point startPos);
    std::string getName() const override;
    std::string getAbilityName() const override;
    std::string useAbility(Board& board, const std::vector<Point>& enemyPositions) override;
};