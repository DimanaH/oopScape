#include "FastEnemy.h"
#include "BFS.h"

FastEnemy::FastEnemy(Point startPos) : Enemy(startPos) {}

char FastEnemy::getSymbol() const { return 'X'; }

std::string FastEnemy::getType() const { return "Speeder"; }

void FastEnemy::move(const Point& heroPos, const Board& board, bool heroInvisible)
{
    if (heroInvisible) return;
    tryMoveTowardsHeroBFS(pos, heroPos, board);
    tryMoveTowardsHeroBFS(pos, heroPos, board);
}