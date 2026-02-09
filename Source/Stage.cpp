#include "../Library/Network.h"
#include "Stage.h"
#include <DxLib.h>


#define CELL 64
#define ORG_X 100
#define ORG_Y 50

extern Network gNet;

Stage::Stage()
    : turn(BLACK), gameEnd(false)
{
}

void Stage::Update()
{
    int mx, my;
    GetMousePoint(&mx, &my);

    if (gNet.IsConnected() && (GetMouseInput() & MOUSE_INPUT_LEFT)) {
        int x = (mx - ORG_X) / CELL;
        int y = (my - ORG_Y) / CELL;
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            gNet.Send("PUT " + std::to_string(x) + " " + std::to_string(y));
        }
    }

    static std::string boardStr;
    if (!gNet.IsConnected()) return;

    std::string msg;
    while (gNet.Recv(msg)) {
        if (msg.find("BOARD") != std::string::npos) {
            boardStr.clear();
            continue;
        }

        for (char c : msg) {
            if (c == 'B' || c == 'W' || c == '.') boardStr += c;
        }

        if (boardStr.size() >= 64) {
            board.SetFromString(boardStr);
            boardStr.clear();
        }
    }
}

void Stage::Draw()
{
    DrawString(10, 480,
        board.Get(3, 3) == WHITE ? "W OK" : "NO W",
        GetColor(255, 255, 0));

    // 盤面描画
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {

            // マス
            DrawBox(
                ORG_X + x * CELL,
                ORG_Y + y * CELL,
                ORG_X + (x + 1) * CELL,
                ORG_Y + (y + 1) * CELL,
                GetColor(0, 128, 0),
                TRUE
            );

            // 枠線
            DrawBox(
                ORG_X + x * CELL,
                ORG_Y + y * CELL,
                ORG_X + (x + 1) * CELL,
                ORG_Y + (y + 1) * CELL,
                GetColor(0, 0, 0),
                FALSE
            );

            // 石
            Stone s = board.Get(x, y);
            if (s != EMPTY) {
                DrawCircle(
                    ORG_X + x * CELL + CELL / 2,
                    ORG_Y + y * CELL + CELL / 2,
                    CELL / 2 - 4,
                    (s == BLACK) ? GetColor(0, 0, 0)
                    : GetColor(255, 255, 255),
                    TRUE
                );
            }
        }
    }

    // ターン表示
    if (!gameEnd) {
        const char* text = (turn == BLACK) ? "BLACK TURN" : "WHITE TURN";
        int color = (turn == BLACK) ? GetColor(0, 0, 0)
            : GetColor(255, 255, 255);

        DrawBox(10, 10, 210, 40, GetColor(0, 150, 0), TRUE);
        DrawString(20, 15, text, color);
    }

    // 結果表示
    if (gameEnd) {
        DrawBox(150, 200, 450, 300, GetColor(0, 0, 0), TRUE);
        DrawString(200, 230, result.c_str(), GetColor(255, 255, 255));
    }
}

