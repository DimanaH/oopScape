#include "Enemy.h"

Enemy::Enemy(Point startPos) : pos(startPos) {}

Point Enemy::getPos() const
{
    return pos;
}