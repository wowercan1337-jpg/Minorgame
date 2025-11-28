#include <iostream>
#include <memory>
#include "Board.h"

int main() {
    int rows = 10, cols = 10, mines = 10;
    auto board = std::make_unique<Board>(rows, cols, mines);

    bool gameOver = false;
    while (!gameOver) {
        board->printBoard();
        std::cout << "Rad Kolumn (r c) och kommando (reveal/flag): ";
        int r, c;
        std::string cmd;
        std::cin >> r >> c >> cmd;

        if (!std::cin || r < 0 || r >= rows || c < 0 || c >= cols) {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout << "Ogiltig inmatning!\n";
            continue;
        }

        if (cmd == "reveal") {
            if (board->isMine(r, c)) {
                std::cout << "Du trampade på en mina! Game Over!\n";
                board->printBoard(true);
                gameOver = true;
            } else {
                board->revealCell(r, c);
                if (board->allCellsRevealed()) {
                    std::cout << "Grattis! Du vann!\n";
                    board->printBoard(true);
                    gameOver = true;
                }
            }
        } else if (cmd == "flag") {
            board->toggleFlag(r, c);
        } else {
            std::cout << "Ogiltigt kommando! Använd reveal eller flag.\n";
        }
    }

    return 0;
}
