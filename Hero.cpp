#include "Hero.h"
#include "Enemy.h"

Hero::Hero(Point startPos) : pos(startPos) {}


Point Hero::getPos() const
{
    return pos;
}

void Hero::setPos(Point p)
{
    pos = p;
}

int Hero::getCooldown() const
{
    return abilityCooldown;
}

void Hero::tickCooldown()
{
    if (abilityCooldown > 0) --abilityCooldown;
}
bool Hero::isInvisible() const
{
    return false;
}
void Hero:: tickInvisibility() {}

bool Hero::move(int dx, int dy, const Board& board)
{
    int newX = pos.x + dx;
    int newY = pos.y + dy;

    if (!board.isWalkable(newX, newY)) return false;

    pos.x = newX;
    pos.y = newY;
    return true;
}