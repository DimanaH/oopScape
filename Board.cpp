#include "Board.h"
#include <fstream>
#include <stdexcept> 

void Board::loadFromFile(const std::string& fileName)
{
    grid.clear();

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + fileName);
    }

    std::string firstLine;
    std::getline(file, firstLine);

    try {
        size = std::stoi(firstLine);
    }
    catch (...) {
        throw std::runtime_error("First line must be a number of symbols (board size).");
    }

    if (size < 2 || size > 64) {
        throw std::runtime_error("Board size must be between 2 and 64.");
    }

    int sCount = 0, fCount = 0;

    for (int row = 0; row < size; row++)
    {
        std::string line;

        if (!std::getline(file, line))
        {
            throw std::runtime_error("Missing rows in level file.");
        }

        if ((int)line.size() != size)
        {
            throw std::runtime_error("Row " + std::to_string(row+1) + " has wrong length.");
        }

        for (int col = 0; col < size; col++)
        {
            char c = line[col];

            if (c != '*' && c != ' ' && c != 'S' && c != 'F' && c != 'E' && c != 'W' && c != 'X') {

                throw std::runtime_error( std::string("Invalid character '") +
                    c + "' at row " + std::to_string(row+1) + ", col " + std::to_string(col+1));
            }
            if (c == 'S') {
                sCount++;
                startPos = {col, row };
            }
            if (c == 'F') { 
                fCount++;
                finishPos = { col, row };
            }
        }

        grid.push_back(line);
    }
    std::string extra;
    if (std::getline(file, extra)) {
        throw std::runtime_error("Too many rows in level file.");
    }

    if (sCount != 1)
    {
        throw std::runtime_error("Board must have exactly one 'S'.");
    }
    if (fCount != 1)
    {
        throw std::runtime_error("Board must have exactly one 'F'.");
    }
}

void Board::print() const
{
    for (int row = 0; row < size; row++) 
    {
        for (int col = 0; col < size; col++) 
        {
            std::cout << grid[row][col];
        }
        std::cout << '\n';
    }
}

bool Board::isInside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < size && y < size;
}

bool Board::isWalkable(int x, int y) const
{
    if (!isInside(x, y)) return false;
    return grid[y][x] != '*';
}

char Board::getCell(int x, int y) const
{
    if (!isInside(x, y)) return '*'; 
    return grid[y][x];
}

void Board::setCell(int x, int y, char c)
{
    if (!isInside(x, y)) return;
    grid[y][x] = c;
}

int Board::getSize() const
{
    return size;
}

Point Board::getStartPos() const
{
    return startPos;
}

Point Board::getFinishPos() const
{
    return finishPos;
}