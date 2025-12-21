#include "playScene.h"
#include "../Library/sceneManager.h"
#include "../Library/resourceLoader.h"
#include <DxLib.h>
#include "GameMain.h"

#include "cloudManager.h"
#include "darkness.h"
#include "boss.h"
#include "attack.h"
#include "judge.h"

PlayScene::PlayScene()
{
	new Boss();
	new Attack();

	new GameMain();//CoGƒo[ƒWƒ‡ƒ“‚ªˆá‚¤(4.1ˆÈã)

	new Judge();

	sound = new Sound();
	sound->SetPlayBGM(Sound::BGM::PLAY, 9500);

	fade = new Fade();
	fade->FadeOutStart(1.0f);

	image = ResourceLoader::LoadGraph("data\\2D\\gameback.png");
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}

	/*if (!fade->FadeEnd())
	{
		sound->StopPlayBGM();
		SceneManager::ChangeScene("TitleScene");
	}*/

	if (FindGameObject<Judge>()->ChangeScene())
	{
		sound->StopPlayBGM();
		SceneManager::ChangeScene("TitleScene");
	}

	SceneBase::Update();
}

void PlayScene::Draw()
{
	/*DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawFormatString(0, 40, GetColor(255, 255, 255), "FPS:%.1f", GetFPS());*/

	SceneBase::Draw();
}
