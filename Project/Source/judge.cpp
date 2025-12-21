#include "judge.h"
#include "fade.h"
#include "sound.h"

#include "../Library/time.h"
#include "../Library/resourceLoader.h"

#include "Screen.h"

Judge::Judge()
{
	image = ResourceLoader::LoadGraph("data\\2D\\endimage.png");
	imageSize = 0.0f;
	sizeSpeed = 0.001f;

	startCounter = 0.0f;
	endCounter = 0.0f;
	gameStart = false;
	gameEnd = false;

	isEndCount = false;

	fadeStart = false;
	changeScene = false;

	isEndSound = false;
}

Judge::~Judge()
{
}

void Judge::Update()
{
	if (startCounter >= 5.0f)
		gameStart = true;
	else
		startCounter += Time::DeltaTime();


	if (isEndCount)
	{
		if(!isEndSound)
		{
			FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::GAME_CLEAR, 10000);
			isEndSound = true;
		}

		if (endCounter > 5.0f)
		{
			gameEnd = true;
		}
		else
			endCounter += Time::DeltaTime();

		imageSize += sizeSpeed;
		sizeSpeed += 0.002f;

		imageSize = std::clamp(imageSize, 0.0f, 1.0f);
	}


	if (gameEnd)
	{
		if (!fadeStart)
		{
			FindGameObject<Fade>()->FadeInStart(2.0f);
		}
		fadeStart = true;
	}

	if (fadeStart && !FindGameObject<Fade>()->FadeEnd())
	{
		changeScene = true;
		//FindGameObject<Sound>()->StopPlayBGM();
		//gameEnd = true;

		//SceneManager::ChangeScene("TitleScene");
		
	}
}

void Judge::Draw()
{
	if (isEndCount)
		DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0, 0, 1024, 1024, imageSize, 0.0f, image, true);
}
