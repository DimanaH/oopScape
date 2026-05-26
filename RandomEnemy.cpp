#include "RandomEnemy.h"
#include <cstdlib>
#include <vector>

RandomEnemy::RandomEnemy(Point startPos) : Enemy(startPos) {}

char RandomEnemy::getSymbol() const { return 'W'; }

std::string RandomEnemy::getType() const { return "Wanderer"; }

void RandomEnemy::move(const Point& heroPos, const Board& board, bool heroInvisible)
{
    std::vector<Point> openCells;
    int n = board.getSize();
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            if (board.isWalkable(x, y) && !(x == pos.x && y == pos.y)&&!(x == heroPos.x && y == heroPos.y))
                openCells.push_back({ x, y });

    if (openCells.empty()) return;
    pos = openCells[std::rand() % openCells.size()];
}