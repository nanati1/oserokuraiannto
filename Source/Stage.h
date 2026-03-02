#pragma once
#include <string>
#include "Board.h"

class Stage {
public:
    Stage();
    void Update();
    void Draw();
    void OnNetworkMessage(const std::string& msg);
    bool gameStarted = false;

private:
    Board board;
    Stone turn = BLACK;
    bool gameEnd = false;
    std::string result;
};