#include "App.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Time.h"
#include "resourceLoader.h"
#include "DOTween.h"
#include <DxLib.h>

void AppInit()
{
	ObjectManager::Init();
	SceneManager::Init();
	Time::Init();
	ResourceLoader::Init();
	DOTween::Initialize();
}

void AppUpdate()
{
	SceneManager::Update();
	ObjectManager::Update();
	DOTween::Update();
}

void AppDraw()
{
	Time::Refresh();
	ObjectManager::Draw();
	SceneManager::Draw();
}

void AppRelease()
{
	//Time::Release();
	SceneManager::Release();
	ObjectManager::Release();
	ResourceLoader::Release();
	DOTween::Release();

	OutputDebugStringA("---------- This app program is finished ----------\n");
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}