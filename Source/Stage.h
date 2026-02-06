#pragma once
#include <string>
#include "Board.h"

class Stage {
public:
    Stage();
    void Update();
    void Draw();
private:
    Board board;          // 表示用
    Stone turn = BLACK;   // サーバーから受信
    bool gameEnd = false; // サーバーから受信
    std::string result;  // サーバーから受信
};