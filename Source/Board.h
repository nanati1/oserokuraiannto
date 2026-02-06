#pragma once
#include <string>

enum Stone { EMPTY, BLACK, WHITE };

class Board {
public:
    Board();

    void SetFromString(const std::string& s); // サーバーから反映
    Stone Get(int x, int y) const;

private:
    Stone board[8][8];
};