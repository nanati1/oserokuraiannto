#include "App.h"
#include "Network.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Time.h"
#include <DxLib.h>

extern Network gNet;

void AppInit()
{
	ObjectManager::Init();
	SceneManager::Init();
	Time::Init();

	// ★ ここで1回だけサーバー接続
	gNet.Connect("192.168.42.109", 50000);

	SceneManager::ChangeScene("TITLE");

}

void AppUpdate()
{
	SceneManager::Update();
	ObjectManager::Update();
}

void AppDraw()
{
	Time::Refresh();
	SceneManager::Draw();
	ObjectManager::Draw();
}

void AppRelease()
{
	ObjectManager::Release();
	SceneManager::Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}