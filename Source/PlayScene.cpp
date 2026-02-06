#include "../Library/WinSockFix.h"   

#include "PlayScene.h"
#include "../Library/Network.h"
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
	stage->Update();

	std::string msg;
	if (gNet.Recv(msg)) {
		if (msg.find("BOARD ") == 0) {

		}
	}

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
