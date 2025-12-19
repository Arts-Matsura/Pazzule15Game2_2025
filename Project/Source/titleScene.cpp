#include "titleScene.h"
#include "../Library/sceneManager.h"
#include <vector>
#include "../Library/time.h"

#include "../Library/resourceLoader.h"
#include "Screen.h"

TitleScene::TitleScene()
{
	
	image = ResourceLoader::LoadGraph("data\\2D\\Title_back.png");
	rogoImage = ResourceLoader::LoadGraph("data\\2D\\Title_rogo.png");
	keyImage = ResourceLoader::LoadGraph("data\\2D\\PRESS_SPACE.png");
	
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("PlayScene");
	}
	SceneBase::Update();
}

void TitleScene::Draw()
{
	//DrawString(0, 0, "Title Scene", GetColor(255, 255, 255));	
	SceneBase::Draw();

	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2,0, 0, 1536, 1024, 1.1f, 0.0f, image, true);
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2 - 100 , 0, 0, 1536, 1024, 0.7f, 0.0f, rogoImage, true);
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2 + 300 , 0, 0, 1536, 1024, 0.5f, 0.0f, keyImage, true);
}

