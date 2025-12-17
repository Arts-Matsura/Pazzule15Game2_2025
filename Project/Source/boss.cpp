#include "boss.h"

#include "cloudManager.h"

#include "../Library/time.h"

Boss::Boss()
{
	int randNum = GetRand(4) + 1;
	/*std::string path = "data\\2D\\boss_0" + std::to_string(randNum) + ".png";*/
	std::string path = "data\\2D\\boss_03.png";
	image = LoadGraph(path.c_str());

	backimage = LoadGraph("data\\2D\\background.png");
	bookimage = LoadGraph("data\\2D\\book.png");
	bookbackimage = LoadGraph("data\\2D\\leftback.png");
	boximage = LoadGraph("data\\2D\\box.png");

	bossName = "ぼすだよ";

	fontHandle = CreateFontToHandle(
		"KHドット道玄坂16", // フォント名
		32,               // サイズ
		3                 // 太さ
	);

	actionCounter = 0.0f;

	cloud = new CloudManager();
	darkness = new Darkness();

	SetBackgroundColor(255, 255, 255);
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (actionCounter > 10.0f)
	{
		actionCounter = -10.0f;
		ACTION nextAction = static_cast<ACTION>(GetRand(ACTION_MAX - 1));

		int sideNum = GetRand(1) + 1;
		int sidePos = GetRand(3);
		int verNum = GetRand(1) + 1;
		int verPos = GetRand(3);

		switch (nextAction)
		{
		case Boss::CLOUD_SIDE:
			
			
			cloud->CreateSide(sideNum);
			if (sideNum > 1)
			{
				if (sidePos > 1)
					cloud->CreateSide(sidePos - 2);
				else
					cloud->CreateSide(sidePos + 2);
			}
			break;
		case Boss::CLOUD_VER:
			

			cloud->CreateVer(verNum);
			if (verNum > 1)
			{
				if (verPos > 1)
					cloud->CreateVer(verPos - 2);
				else
					cloud->CreateVer(verPos + 2);
			}
			break;
		case Boss::DARKNESS:
			darkness->EffectStart();
			break;
		}
	}
	else
		actionCounter += Time::DeltaTime();
}

void Boss::Draw()
{
	
	DrawRectRotaGraph(200, 450, 0, 0, 1024, 732, 1.3f, 0.0f, bookbackimage, true);
	DrawRectRotaGraph(390, 450, 0, 0, 788, 900, 1.05f, 0.0f, bookimage, true);
	DrawRectRotaGraph(1200, 400, 0, 0, 1024, 1024, 1.0f, 0.0f, backimage, true);
	DrawRectRotaGraph(410, 400, 0, 0, 504, 504, 1.2f, 0.0f, boximage, true);


	//DrawBox(100, 100, 2000, 2000, GetColor(0, 0, 0), TRUE);
	DrawRectRotaGraph(1200, 300, 0, 0, 260, 260, 1.6f, 0.0f, image, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(850, 600, 1550, 800, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(850, 600, 1550, 800, GetColor(255, 255, 255), FALSE);

	

	std::string serihu = bossName + "があらわれた！！";

	DrawStringToHandle(
		900, 650,
		serihu.c_str(),
		GetColor(255, 255, 255),
		fontHandle
	);
}
