#include "../Library/Network.h"
#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"

extern Network gNet;

PlayScene::PlayScene()
{
    stage = new Stage();
}

PlayScene::~PlayScene()
{
    delete stage;
}

void PlayScene::Update()
{
    DrawString(10, 10, "UPDATE START", GetColor(255, 0, 0));

    // ★ ネットワーク受信はここだけ
    std::string msg;
    while (gNet.Recv(msg)) {
        stage->OnNetworkMessage(msg);
    }

    stage->Update();

    if (CheckHitKey(KEY_INPUT_T)) {
        SceneManager::ChangeScene("TITLE");
    }
}

void PlayScene::Draw()
{
    stage->Draw();

    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
    DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}