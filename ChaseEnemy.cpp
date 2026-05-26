#include "ChaseEnemy.h"
#include "BFS.h"

ChaseEnemy::ChaseEnemy(Point startPos) : Enemy(startPos) {}

char ChaseEnemy::getSymbol() const { return 'E'; }

std::string ChaseEnemy::getType() const { return "Chaser"; }

void ChaseEnemy::move(const Point& heroPos, const Board& board, bool heroInvisible)
{
    if (heroInvisible) return;
    tryMoveTowardsHeroBFS(pos, heroPos, board);
}