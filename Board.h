#pragma once
#include <vector>
#include "Cell.h"

class Board {
public:
    Board(int rows, int cols, int numMines);

    void revealCell(int row, int col);
    void toggleFlag(int row, int col);
    bool isMine(int row, int col) const;
    int getAdjacentMines(int row, int col) const;
    bool allCellsRevealed() const;
    void printBoard(bool revealMines = false) const;

private:
    int rows;
    int cols;
    int numMines;
    std::vector<std::vector<Cell>> board;

    void placeMines();
    void calculateAdjacentMines();
    void revealAdjacentZeros(int row, int col);
    bool validPosition(int row, int col) const;
};
