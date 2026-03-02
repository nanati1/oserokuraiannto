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
    DrawFormatString(10, 520, GetColor(255, 255, 255),
        "CONNECTED=%d", gNet.IsConnected());
    static std::string buffer;

    DrawFormatString(10, 580, GetColor(255, 255, 255),
        "BUF SIZE=%d", buffer.size());

    std::string msg;
    while (gNet.Recv(msg)) {
        buffer += msg + "\n";  // ←全部ためる
    }

    // まとめて処理
    size_t start = buffer.find("BOARD\n");
    size_t end = buffer.find("END_BOARD\n");

    if (start != std::string::npos && end != std::string::npos) {
        std::string data = buffer.substr(start + 6, end - (start + 6));

        if (data.size() >= 64) {
            board.SetFromString(data.substr(0, 64));
        }

        buffer.erase(0, end + 10);
    }
}

void Stage::OnNetworkMessage(const std::string& msg)
{
    static bool receiving = false;
    static std::string boardStr;

    if (msg == "BOARD")
    {
        boardStr.clear();
        receiving = true;
        return;
    }

    if (msg == "END_BOARD")
    {
        if (boardStr.size() == 64)
            board.SetFromString(boardStr);

        receiving = false;
        return;
    }

    if (receiving)
    {
        // 改行や空白を除去
        for (char c : msg)
        {
            if (c == '.' || c == 'B' || c == 'W')
                boardStr += c;
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