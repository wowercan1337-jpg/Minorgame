#include "Board.h"
#include <iostream>
#include <random>
#include <queue>

Board::Board(int r, int c, int mines) : rows(r), cols(c), numMines(mines) {
    board.resize(rows, std::vector<Cell>(cols));
    placeMines();
    calculateAdjacentMines();
}

void Board::placeMines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, rows - 1);
    std::uniform_int_distribution<> colDist(0, cols - 1);

    int placed = 0;
    while (placed < numMines) {
        int r = rowDist(gen);
        int c = colDist(gen);
        if (!board[r][c].hasMine) {
            board[r][c].hasMine = true;
            placed++;
        }
    }
}

void Board::calculateAdjacentMines() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!board[r][c].hasMine) {
                int count = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        int nr = r + dr, nc = c + dc;
                        if (validPosition(nr, nc) && board[nr][nc].hasMine)
                            count++;
                    }
                }
                board[r][c].adjacentMines = count;
            }
        }
    }
}

bool Board::validPosition(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Board::revealCell(int row, int col) {
    if (!validPosition(row, col) || board[row][col].revealed || board[row][col].flagged)
        return;

    board[row][col].revealed = true;

    if (board[row][col].adjacentMines == 0 && !board[row][col].hasMine) {
        revealAdjacentZeros(row, col);
    }
}

void Board::revealAdjacentZeros(int row, int col) {
    std::queue<std::pair<int,int>> q;
    q.push({row, col});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                int nr = r + dr;
                int nc = c + dc;
                if (validPosition(nr, nc) && !board[nr][nc].revealed && !board[nr][nc].hasMine) {
                    board[nr][nc].revealed = true;
                    if (board[nr][nc].adjacentMines == 0)
                        q.push({nr, nc});
                }
            }
        }
    }
}

void Board::toggleFlag(int row, int col) {
    if (validPosition(row, col) && !board[row][col].revealed)
        board[row][col].flagged = !board[row][col].flagged;
}

bool Board::isMine(int row, int col) const {
    return validPosition(row, col) && board[row][col].hasMine;
}

int Board::getAdjacentMines(int row, int col) const {
    return validPosition(row, col) ? board[row][col].adjacentMines : 0;
}

bool Board::allCellsRevealed() const {
    for (const auto& row : board)
        for (const auto& cell : row)
            if (!cell.hasMine && !cell.revealed)
                return false;
    return true;
}

void Board::printBoard(bool revealMines) const {
    std::cout << "  ";
    for (int c = 0; c < cols; ++c) std::cout << c << " ";
    std::cout << "\n";

    for (int r = 0; r < rows; ++r) {
        std::cout << r << " ";
        for (int c = 0; c < cols; ++c) {
            const Cell& cell = board[r][c];
            if (cell.revealed) {
                if (cell.hasMine) std::cout << "* ";
                else if (cell.adjacentMines > 0) std::cout << cell.adjacentMines << " ";
                else std::cout << "  ";
            } else if (cell.flagged) {
                std::cout << "F ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}
