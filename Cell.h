#pragma once

struct Cell {
    bool hasMine = false;      // Om cellen innehåller en mina
    bool revealed = false;     // Om cellen har avslöjats
    bool flagged = false;      // Om spelaren har flaggat cellen
    int adjacentMines = 0;     // Antal minor i angränsande rutor
};
