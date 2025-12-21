#include "resultScene.h"
#include "../Library/sceneManager.h"
#include <vector>
#include "../Library/time.h"

#include "../Library/resourceLoader.h"
#include "Screen.h"

ResultScene::ResultScene()
{
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
	SceneBase::Update();
}

void ResultScene::Draw()
{
	SceneBase::Draw();
}
