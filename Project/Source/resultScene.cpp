#include "resultScene.h"
#include "../Library/sceneManager.h"
#include <vector>
#include "../Library/time.h"

#include "../Library/resourceLoader.h"
#include "Screen.h"

ResultScene::ResultScene()
{
	image = ResourceLoader::LoadGraph("data\\2D\\resultBack.png");

	isPushKey = false;

	sound = new Sound();
	sound->SetPlayBGM(Sound::BGM::TITLE, 9000);

	fade = new Fade();
	fade->FadeOutStart(1.0f);
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && !isPushKey) {

		isPushKey = true;
		sound->SetPlaySound(Sound::SOUND::START, 10000);
		fade->FadeInStart(2.0f);
	}

	if (isPushKey && !fade->FadeEnd())
	{
		sound->StopPlayBGM();
		SceneManager::ChangeScene("TitleScene");
	}

	SceneBase::Update();
}

void ResultScene::Draw()
{
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0, 0, 1536, 1024, 1.05f, 0.0f, image, true);
	fade->Draw();
	SceneBase::Draw();
}
