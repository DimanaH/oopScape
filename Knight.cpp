#include "Knight.h"

Knight::Knight(Point startPos) : Hero(startPos) {}

std::string Knight::getName() const
{
    return "Knight";
}

std::string Knight::getAbilityName() const
{
    return "Smash";
}

std::string Knight::useAbility(Board& board, const std::vector<Point>& enemyPositions)
{
    if (abilityCooldown > 0)
        return "Smash on cooldown! (" + std::to_string(abilityCooldown) + " turns left)";

    int dx[] = { -1, 1,  0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    int destroyed = 0;
    for (int k = 0; k < 4; k++) {
        int nx = pos.x + dx[k];
        int ny = pos.y + dy[k];
        if (board.isInside(nx, ny) && board.getCell(nx, ny) == '*') {
            board.setCell(nx, ny, ' ');
            destroyed++;
        }
    }

    abilityCooldown = 4;
    return "Smash! Destroyed " + std::to_string(destroyed) + " wall(s)!";
}