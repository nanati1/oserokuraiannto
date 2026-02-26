#include "Board.h"
#include <string>

Board::Board() {
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            board[x][y] = EMPTY;
}

// š Š®‘SC³”Å
void Board::SetFromString(const std::string& s) {
    int idx = 0;

    for (char c : s)
    {
        if (c != 'B' && c != 'W' && c != '.') continue;

        int x = idx % 8;
        int y = idx / 8;

        if (c == 'B') board[x][y] = BLACK;
        else if (c == 'W') board[x][y] = WHITE;
        else board[x][y] = EMPTY;

        idx++;
        if (idx >= 64) break;
    }

    printf("idx = %d\n", idx); // šŠm”F
}

Stone Board::Get(int x, int y) const {
    return board[x][y];
}