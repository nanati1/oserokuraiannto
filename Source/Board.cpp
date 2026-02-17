#include "Board.h"

Board::Board() {
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            board[x][y] = EMPTY;
}

void Board::SetFromString(const std::string& s) {
    if (s.size() < 64) return; // © ’Ç‰Á
    int idx = 0;

    for (char c : s) {
        if (c == '\n') continue; // ‰üs‚Í–³‹

        int x = idx % 8;
        int y = idx / 8;

        if (c == 'B') board[x][y] = BLACK;
        else if (c == 'W') board[x][y] = WHITE;
        else board[x][y] = EMPTY;

        idx++;
        if (idx >= 64) break;
    }
}

Stone Board::Get(int x, int y) const {
    return board[x][y];
}