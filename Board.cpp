#include "Board.h"
#include <fstream>
#include <stdexcept> 

void Board::loadFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + fileName);
    }

    std::string firstLine;
    std::getline(file, firstLine);

    try {
        size = std::stoi(firstLine);
    }
    catch (...) {
        throw std::runtime_error("First line must be a number (board size).");
    }

    if (size < 2 || size > 64) {
        throw std::runtime_error("Board size must be between 2 and 64.");
    }

    int sCount = 0, fCount = 0;

    for (size_t row = 0; row < size; row++) {
        std::string line;
        std::getline(file, line);

        if (line.size() != size) {
            throw std::runtime_error("Row " + std::to_string(row) + " has wrong length.");
        }

        for (size_t col = 0; col < size; col++) {
            char c = line[col];

            if (c != '*' && c != ' ' && c != 'S' && c != 'F' && c != 'E') {

                throw std::runtime_error( std::string("Invalid character '") + c + "' at row " +
                    std::to_string(row) + ", col " + std::to_string(col));
            }
            if (c == 'S') { sCount++; startPos = { (int)col, (int)row }; }
            if (c == 'F') { fCount++; finishPos = { (int)col, (int)row }; }
        }

        grid.push_back(line);
    }

    if (sCount != 1) throw std::runtime_error("Board must have exactly one 'S'.");
    if (fCount != 1) throw std::runtime_error("Board must have exactly one 'F'.");
}

void Board::print() const
{
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
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