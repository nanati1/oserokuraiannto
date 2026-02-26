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
    //board.SetFromString(
    //    "........"
    //    "........"
    //    "........"
    //    "...WB..."
    //    "...BW..."
    //    "........"
    //    "........"
    //    "........"
    //);

    //// ←ここ！！！！
    //if (board.Get(3, 3) == WHITE)
    //{
    //    printf("W OK\n");
    //}
    //else
    //{
    //    printf("NO W\n");
    //}
}

void Stage::Update()
{
    static int prev = 0;

    int mx, my;
    GetMousePoint(&mx, &my);

    int now = GetMouseInput();

    // クリック瞬間だけ検出
    if (gNet.IsConnected() &&
        (now & MOUSE_INPUT_LEFT) &&
        !(prev & MOUSE_INPUT_LEFT))
    {
        // 盤面内だけ
        if (mx >= ORG_X && mx < ORG_X + 8 * CELL &&
            my >= ORG_Y && my < ORG_Y + 8 * CELL)
        {
            int x = (mx - ORG_X) / CELL;
            int y = (my - ORG_Y) / CELL;

            printf("CLICK x=%d y=%d\n", x, y); // デバッグ

            gNet.Send("PUT " + std::to_string(x) + " " + std::to_string(y));
        }
    }

    prev = now;
}

void Stage::OnNetworkMessage(const std::string& msg)
{
    printf("msg = [%s]\n", msg.c_str()); // ←これ追加
    static std::string boardStr;
    static bool receivingBoard = false;

    // BOARD開始
    if (msg.find("BOARD") != std::string::npos) {
        boardStr.clear();
        receivingBoard = true;
    }

    // 受信中
    if (receivingBoard) {
        for (char c : msg) {
            if (c == 'B' || c == 'W' || c == '.') {
                boardStr += c;
            }
        }

        if (boardStr.size() >= 64) {
            board.SetFromString(boardStr);
            boardStr.clear();
            receivingBoard = false;
        }
    }
}

void Stage::Draw()
{
    DrawString(10, 480,
        board.Get(3, 3) == WHITE ? "W OK" : "NO W",
        GetColor(255, 255, 0));

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {

            DrawBox(
                ORG_X + x * CELL,
                ORG_Y + y * CELL,
                ORG_X + (x + 1) * CELL,
                ORG_Y + (y + 1) * CELL,
                GetColor(0, 128, 0),
                TRUE
            );

            DrawBox(
                ORG_X + x * CELL,
                ORG_Y + y * CELL,
                ORG_X + (x + 1) * CELL,
                ORG_Y + (y + 1) * CELL,
                GetColor(0, 0, 0),
                FALSE
            );

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
}