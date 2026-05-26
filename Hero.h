#pragma once
#include "Point.h"
#include "Board.h"
#include <string>
#include <vector> 
class Hero
{
protected:
    Point pos;
    int abilityCooldown = 0;

public:
    Hero(Point startPos);
    virtual ~Hero() = default;

    virtual std::string getName() const = 0;
    virtual std::string getAbilityName() const = 0;
    virtual std::string useAbility(Board& board, const std::vector<Point>& enemyPositions) = 0;

    Point getPos() const;
    void setPos(Point p);
    int getCooldown() const;
    void tickCooldown();
    virtual bool isInvisible() const;
    virtual void tickInvisibility();
    bool move(int dx, int dy, const Board& board);
};
