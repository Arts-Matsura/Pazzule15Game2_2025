#include "titleScene.h"
#include "../Library/sceneManager.h"
#include <vector>
#include "../Library/time.h"

#include "../Library/resourceLoader.h"
#include "Screen.h"

#include "sound.h"

TitleScene::TitleScene()
{
	
	image = ResourceLoader::LoadGraph("data\\2D\\Title_back.png");
	rogoImage = ResourceLoader::LoadGraph("data\\2D\\Title_rogo.png");
	keyImage = ResourceLoader::LoadGraph("data\\2D\\PRESS_SPACE.png");
	
	imagePosX = 0.0f;
	imagePosY = 0.0f;
	moveX = 0.5f;
	moveY = 0.5f;

	sizeFrame = 0.0f;

	sound = new Sound();
	sound->SetPlayBGM(Sound::BGM::TITLE, 9000);

	fade = new Fade();
	fade->FadeOutStart(1.0f);

	isPushKey = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_V)) {
		sound->SetPlaySound(Sound::SOUND::GAME_CLEAR, 10000);
	}

	if (CheckHitKey(KEY_INPUT_SPACE)&&!isPushKey) {
		
		isPushKey = true;
		sound->SetPlaySound(Sound::SOUND::START, 10000);
		fade->FadeInStart(2.0f);
	}

	if (isPushKey && !fade->FadeEnd())
	{
		sound->StopPlayBGM();
		SceneManager::ChangeScene("PlayScene");
	}

	if (imagePosX > 40)
		moveX = -0.5f;
	else if (imagePosX < -40)
		moveX = 0.5f;

	if (imagePosY > 25)
		moveY = -0.5f;
	else if (imagePosY < -25)
		moveY = 0.5f;

	imagePosX += moveX;
	imagePosY += moveY;

	sizeFrame += 0.02f;

	SceneBase::Update();
}

void TitleScene::Draw()
{
	//DrawString(0, 0, "Title Scene", GetColor(255, 255, 255));	
	DrawRectRotaGraph(Screen::WIDTH / 2 + imagePosX, Screen::HEIGHT / 2 + imagePosY, 0, 0, 1536, 1024, 1.1f, 0.0f, image, true);
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2 - 100, 0, 0, 1536, 1024, 0.7f, 0.0f, rogoImage, true);
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2 + 300, 0, 0, 1536, 1024, 0.5f + 0.2f * sinf(sizeFrame), 0.0f, keyImage, true);

	fade->Draw();

	SceneBase::Draw();

}

