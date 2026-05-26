#pragma once
#include "Board.h"
#include "Hero.h"
#include "Enemy.h"
#include "ChaseEnemy.h"
#include "RandomEnemy.h"
#include "FastEnemy.h"
#include "Color.h"    

#include <vector>
#include <memory>
#include <string>

enum class GameResult { Win, Loss };

class Game
{
private:
    Board board;
    std::unique_ptr<Hero> hero;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::string lastMessage = "";

    void render(const std::string& message) const;
    bool processCommand(const std::string& cmd, std::string& message); 
    std::string getCommand() const;
    void moveEnemies();
    bool enemyOnHero() const;

    bool isEnemy(const Point& p) const;
    char enemySymbolAt(const Point& p) const;
public:
    Game(const std::string& levelFile, std::unique_ptr<Hero> hero);
    GameResult run();
    std::unique_ptr<Hero> releaseHero();
};