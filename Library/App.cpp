#include "WinSockFix.h"
#include "Network.h"
#include "App.h"
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

	if (!gNet.Connect("192.168.42.109", 50000)) {
		MessageBox(nullptr, "CONNECT FAILED", "ERROR", MB_OK);
		return;
	}
	MessageBox(nullptr, "AFTER CONNECT", "DEBUG", MB_OK);

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