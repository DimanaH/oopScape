#include "Game.h"
#include "Rogue.h"
#include "Color.h"    
#include <iostream>
#include <algorithm>


Game::Game(const std::string& levelFile, std::unique_ptr<Hero> h) : hero(std::move(h))
{
    board.loadFromFile(levelFile);

    int n = board.getSize();
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            char c = board.getCell(x, y);
            if (c == 'E')
                enemies.push_back(std::make_unique<ChaseEnemy>(Point{ x, y }));
            else if (c == 'W')
                enemies.push_back(std::make_unique<RandomEnemy>(Point{ x, y }));
            else if (c == 'X')
                enemies.push_back(std::make_unique<FastEnemy>(Point{ x, y }));
        }
    }

    board.setCell(hero->getPos().x, hero->getPos().y, ' ');
    for (auto& e : enemies)
        board.setCell(e->getPos().x, e->getPos().y, ' ');
}

bool Game::isEnemy(const Point& p) const
{
    for (const auto& e : enemies)
        if (e->getPos().x == p.x && e->getPos().y == p.y)
            return true;
    return false;
}

char Game::enemySymbolAt(const Point& p) const
{
    for (const auto& e : enemies)
        if (e->getPos().x == p.x && e->getPos().y == p.y)
            return e->getSymbol();
    return '?';
}

void Game::render(const std::string& message) const
{
    system("cls");//clears the console

    int n = board.getSize();

    printColored("    ", Color::Cyan);
    for (int x = 0; x < n; x++) {//the first row
        std::string num = std::to_string(x);
        if (num.size() == 2) num = " " + num;
        if (num.size() == 1) num = " " + num;

        printColored(num, Color::Cyan);
    }
    std::cout << "\n";

    printColored("    ", Color::Cyan);
    for (int x = 0; x < n * 2 + 1; x++)
        printColored("-", Color::Cyan);
    std::cout << "\n";

    for (int y = 0; y < n; y++)
    {
        std::string rowNum = std::to_string(y);
        if (rowNum.size() == 1) rowNum = " " + rowNum;
        printColored(rowNum + " | ", Color::Cyan);

        for (int x = 0; x < n; x++)
        {
            Point p{ x, y };

            if (p.x == hero->getPos().x && p.y == hero->getPos().y)
                printColored("H ", Color::Yellow);
            else if (isEnemy(p))
                printColored(std::string(1, enemySymbolAt(p)) + " ", Color::Red);
            else if (board.getCell(x, y) == 'F')
                printColored("F ", Color::White);
            else if (board.getCell(x, y) == '*')
                printColored("* ", Color::Cyan);
            else
                std::cout << "  "; 
        }
        std::cout << "\n";
    }

    printColored("    ", Color::Cyan);
    for (int x = 0; x < n * 2 + 1; x++)
        printColored("-", Color::Cyan);
    std::cout << "\n";

    printColored("    ", Color::Cyan);
    for (int x = 0; x < n; x++) {//the last row
        std::string num = std::to_string(x);
        if (num.size() == 2) num = " " + num;
        if (num.size() == 1) num = " " + num;

        printColored(num, Color::Cyan);
    }
    std::cout << "\n";

    if (!message.empty())
        printColored(">> " + message + "\n", Color::Yellow);

    printColored("Command U/L/D/R or OOP): ", Color::Cyan);
}

GameResult Game::run()
{
    while (true) {
        render(lastMessage);

        std::string cmd;
        do {
            cmd = getCommand();
        } while (cmd.empty());
        bool validMove = processCommand(cmd, lastMessage);

        if (validMove&& cmd!="OOP") {
            if (board.getCell(hero->getPos().x, hero->getPos().y) == 'F')
                return GameResult::Win;
            if (enemyOnHero())
                return GameResult::Loss;

            moveEnemies();

            if (enemyOnHero())
                return GameResult::Loss;

            hero->tickCooldown();
            hero->tickInvisibility();

        }
    }
}

std::unique_ptr<Hero> Game::releaseHero()
{
    return std::move(hero);
}


std::string Game::getCommand() const
{
    std::cout << "> ";
    std::string cmd;
    std::getline(std::cin, cmd);
    for (char& c : cmd) c = (char)std::toupper((unsigned char)c);
    return cmd;
}


bool Game::processCommand(const std::string& cmd, std::string& message)
{
    if (cmd == "Q") exit(0);

    if (cmd == "OOP") {
        std::vector<Point> enemyPos;
        for (const auto& e : enemies)
            enemyPos.push_back(e->getPos());
        message = hero->useAbility(board, enemyPos);
        return true;
    }

    int dx = 0, dy = 0;
    if (cmd == "U") dy = -1;
    else if (cmd == "D") dy = 1;
    else if (cmd == "L") dx = -1;
    else if (cmd == "R") dx = 1;
    else {
        message = "Unknown command! Use U/D/L/R, OOP or Q.";
        return false; 
    }

    if (!hero->move(dx, dy, board)) {
        message = "Can't move there is a wall!";
        return false; 
    }

    message = "";
    return true;
}


void Game::moveEnemies()
{
    bool heroInvisible = hero->isInvisible();

    for (auto& e : enemies)
        e->move(hero->getPos(), board, heroInvisible);
}

bool Game::enemyOnHero() const
{
    for (const auto& e : enemies)
        if (e->getPos().x == hero->getPos().x && 
            e->getPos().y == hero->getPos().y)
            return true;
    return false;
}