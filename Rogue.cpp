#include "Rogue.h"

Rogue::Rogue(Point startPos) : Hero(startPos) {}

std::string Rogue::getName() const
{
    return "Rogue";
}

std::string Rogue::getAbilityName() const
{
    return "Shadow Veil";
}

std::string Rogue::useAbility(Board& board, const std::vector<Point>& enemyPositions)
{
    if (abilityCooldown > 0)
        return "Shadow Veil on cooldown! (" + std::to_string(abilityCooldown) + " turns left)";

    invisible = true;
    invisTurns = 3;
    abilityCooldown = 6;
    return "Shadow Veil! You are invisible for 3 turns!";
}

bool Rogue::isInvisible() const
{
    return invisible;
}

void Rogue::tickInvisibility()
{
    if (invisTurns > 0) {
        --invisTurns;
        if (invisTurns == 0) invisible = false;
    }
}