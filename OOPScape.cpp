#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Game.h"
#include "Wizard.h"
#include "Knight.h"
#include "Rogue.h"

static const std::vector<std::string> LEVELS = {
    "levels/level1.txt",
    "levels/level2.txt",
    "levels/level3.txt"
};

std::unique_ptr<Hero> chooseHero(Point startPos)
{
    while (true) {
        std::cout << "\n=== Choose your hero ===\n";
        std::cout << "1. Wizard - Teleport to random cell (cooldown: 5)\n";
        std::cout << "2. Knight - Attack walls infront (cooldown: 4)\n";
        std::cout << "3. Rogue - Invisible for 3 turns (cooldown: 6)\n";
        std::cout << "> ";

        std::string line;
        std::getline(std::cin, line);

        if (line == "1") return std::make_unique<Wizard>(startPos);
        if (line == "2") return std::make_unique<Knight>(startPos);
        if (line == "3") return std::make_unique<Rogue>(startPos);

        std::cout << "Invalid choice! Please enter 1, 2 or 3.\n";
    }
}

int main()
{
    system("cls");
    std::cout << "================================\n";
    std::cout << "            OOPScape            \n";
    std::cout << "================================\n";

    Board firstBoard;
    try {
        firstBoard.loadFromFile(LEVELS[0]);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    std::unique_ptr<Hero> hero = chooseHero(firstBoard.getStartPos());

    for (int i = 0; i < (int)LEVELS.size(); i++)
    {
        std::cout << "\n=== Level " << (i + 1) << " ===  Press Enter...";

        Board levelBoard;
        try {
            levelBoard.loadFromFile(LEVELS[i]);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            return 1;
        }

        hero->setPos(levelBoard.getStartPos());

        Game game(LEVELS[i], std::move(hero));
        GameResult result = game.run();

        if (result == GameResult::Loss)
        {
            std::cout << "\n=== GAME OVER ===\n";
            std::cout << "Press Enter to exit...";
            std::cin.ignore();
            return 0;
        }

        std::cout << "\n=== LEVEL " << (i + 1) << " COMPLETE! ===\n";

        hero = game.releaseHero();//now main owns hero
    }

    std::cout << "\n=== YOU WIN! ALL LEVELS COMPLETE! ===\n";
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
}