#pragma once
#include "Hero.h"

class Rogue : public Hero
{
private:
    bool invisible = false;
    int invisTurns = 0;
public:
    Rogue(Point startPos);
    std::string getName() const override;
    std::string getAbilityName() const override;
    std::string useAbility(Board& board, const std::vector<Point>& enemyPositions) override;

    bool isInvisible() const override;
    void tickInvisibility() override;
};
