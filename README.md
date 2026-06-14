README — Minesweeper — Console Game in C++
Purpose
Console-based Minesweeper in C++ demonstrating game logic, user input handling, error checking, and modern C++ memory management with smart pointers.

Main features (pass criteria)
Board as a 2D grid with a preset number of mines placed randomly.
Text UI: commands to reveal a cell or flag/unflag a cell by coordinates.
Game rules:
Revealing a mine = loss.
Revealing a non-mine shows the number of adjacent mines.
Win when all non-mine cells are revealed.
Input validation to handle invalid coordinates/commands without crashing.
Clean code structure with clear function and variable names.
Modern memory management: heap-allocated main objects managed via smart pointers (e.g., std::unique_ptr).
Project structure
Headers: Game.h, Board.h, Cell.h, UI.h
Implementations: Game.cpp, Board.cpp, Cell.cpp, UI.cpp, main.cpp
Build: g++ -std=c++17 *.cpp -o minesweeper
Technical summary
Board holds a 2D vector of Cell objects; mines are placed randomly at game start.
Cell stores: isMine, isRevealed, isFlagged, adjacentMineCount.
Game manages state, win/lose detection, and coordinates with UI.
UI parses commands (e.g., "reveal 2 3", "flag 4 1"), validates input and calls Game methods.
Primary heap objects (Board, Game) are owned by smart pointers to ensure safe cleanup*
