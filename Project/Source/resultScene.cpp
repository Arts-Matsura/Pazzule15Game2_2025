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
	sound->SetPlayBGM(Sound::BGM::RESULT, 9000);

	fade = new Fade();
	fade->FadeOutStart(1.0f);

	fontHandle = CreateFontToHandle(
		"KHドット道玄坂16", // フォント名
		55,               // サイズ
		6                 // 太さ
	);
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
	
	DrawFormatStringToHandle(
		Screen::WIDTH / 2 + 5, Screen::HEIGHT / 2,
		GetColor(0, 0, 0),
		fontHandle,
		"世界は救われ、物語は続く。"
	);
	DrawFormatStringToHandle(
		Screen::WIDTH / 2, Screen::HEIGHT / 2,
		GetColor(255, 255, 255),
		fontHandle,
		"世界は救われ、物語は続く。"
	);
	
	fade->Draw();
	SceneBase::Draw();
}
