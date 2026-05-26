#include "Wizard.h"
#include <cstdlib>
#include <vector>


Wizard::Wizard(Point startPos) : Hero(startPos) {}

std::string Wizard::getName() const
{
    return "Wizard";
}

std::string Wizard::getAbilityName() const
{
    return "Teleport";
}

std::string Wizard::useAbility(Board& board, const std::vector<Point>& enemyPositions)
{
    if (abilityCooldown > 0)
        return "Teleport on cooldown! (" + std::to_string(abilityCooldown) + " turns left)";

    std::vector<Point> openCells;
    int n = board.getSize();
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (board.isWalkable(x, y) && !(x == pos.x && y == pos.y))
            {
                bool onEnemy = false;
                for (const auto& ep : enemyPositions)
                {
                    if (ep.x == x && ep.y == y) 
                    { 
                        onEnemy = true; 
                        break;
                    }
                }
                if (!onEnemy)
                    openCells.push_back({ x, y });
            }
        }
    }


    pos = openCells[std::rand() % openCells.size()];//chooses random free cell to escape
    abilityCooldown = 5;
    return "Wizard teleported!";
}