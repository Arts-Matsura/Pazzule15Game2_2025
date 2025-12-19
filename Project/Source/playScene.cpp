#include "playScene.h"
#include "../Library/sceneManager.h"
#include <DxLib.h>
#include "GameMain.h"

#include "cloudManager.h"
#include "darkness.h"
#include "boss.h"
#include "attack.h"

PlayScene::PlayScene()
{

	new Boss();
	new Attack();

	new GameMain();//CoGÉoÅ[ÉWÉáÉìÇ™à·Ç§(4.1à»è„)
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	

	SceneBase::Draw();

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawFormatString(0, 40, GetColor(255, 255, 255), "FPS:%.1f", GetFPS());
}
