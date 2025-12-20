#include "boss.h"

#include "cloudManager.h"
#include "sound.h"

#include "../Library/time.h"

namespace {
	static const int FLASH_INTERVAL = 5; // 点滅周期（小さいほど速い）
	static const int DAMAGE_INTERVAL = 2; // ダメージ振動（上と同様）
}

Boss::Boss()
{
	int randNum = GetRand(4) + 1;
	std::string path = "data\\2D\\boss_0" + std::to_string(randNum) + ".png";
	//std::string path = "data\\2D\\boss_03.png";
	image = LoadGraph(path.c_str());

	path = "data\\2D\\boss_white_0" + std::to_string(randNum) + ".png";
	whiteimage = LoadGraph(path.c_str());

	path = "data\\2D\\background_0" + std::to_string(randNum) + ".png";
	backimage = LoadGraph(path.c_str());
	bookimage = LoadGraph("data\\2D\\book.png");
	bookbackimage = LoadGraph("data\\2D\\leftback.png");
	boximage = LoadGraph("data\\2D\\box.png");

	bossName = "ぼすだよ";

	fontHandle = CreateFontToHandle(
		"KHドット道玄坂16", // フォント名
		50,               // サイズ
		6                 // 太さ
	);

	fontOutHandle = CreateFontToHandle(
		"KHドット道玄坂16", // フォント名
		56,               // サイズ
		7                 // 太さ
	);

	actionCounter = 0.0f;

	cloud = new CloudManager();
	darkness = new Darkness();
	sentence = new Sentence(randNum);

	SetBackgroundColor(255, 255, 255);

	nowAction = ACTION::ACTION_MAX;
	pattern = PATTERN::STAY;

	isActionMessage = false;

	isAttack = false;
	isDamage = false;
	flashFrame = 0;

	for(int i=0;i<3;i++)
	{
		damagePos[i].x = 0.0f;
		damagePos[i].y = 0.0f;
	}

	HP = 5;

	hitStop = 0.0f;

	isDead = false;
	posY = 300;
	sizeY = 260;
	downCounter = 0.0f;
	downSpeed = 5;

	isInversion = false;
	inversionTime = 0.0f;
	inversionLevel = 1.0f;
	inversionState = INVERSION_STATE::INVERSION_START;

	boxPos.x = 40.0f;
	boxPos.y = 100.0f;
}

Boss::~Boss()
{
}

void Boss::Update()
{
	ACTION nextAction = static_cast<ACTION>(GetRand(ACTION_MAX - 1));
	int sideNum = GetRand(1) + 1;
	int sidePos = GetRand(3);
	int verNum = GetRand(1) + 1;
	int verPos = GetRand(3);

	if (hitStop > 0.0f)
	{
		hitStop -= Time::DeltaTime();
		if (hitStop <= 0.0f && HP <= 0)
		{
			isAttack = false;
			isDamage = false;
			pattern = PATTERN::DEAD;
		}

	}

	if (isInversion)
	{
		inversionTime += Time::DeltaTime();
		if (inversionTime > 9.0f)
			inversionState = INVERSION_STATE::RETURN;
		
		switch (inversionState)
		{
		case Boss::INVERSION_START:
			inversionLevel -= 0.05f;
			break;
		case Boss::RETURN:
			inversionLevel += 0.05f;
			break;
		}
		inversionLevel = std::clamp(inversionLevel, -1.0f, 1.0f);

		if (inversionTime > 10.0f)
		{
			isInversion = false;
			inversionTime = 0.0f;
			inversionLevel = 1.0f;
			inversionState = INVERSION_STATE::INVERSION_START;
		}
	}

	if ((isAttack || isDamage) && hitStop <= 0.0f)
	{
		flashFrame++;
		if (isDamage && (flashFrame / FLASH_INTERVAL) % 2 == 0)
		{
			/*isDamage = false;
			flashFrame = 0;*/


			for (int i = 0; i < 3; i++)
			{
				damagePos[i].x = 50 * (sinf(rand()));
				damagePos[i].y = 50 * (sinf(rand()));
			}
		}
		
	}
	else
		flashFrame = 0;

	switch (pattern)
	{
	case Boss::ATTACK_START:

		if (isAttack && flashFrame > 90)
		{
			isAttack = false;
			flashFrame = 0;

			
			switch (nowAction)
			{
			case Boss::CLOUD_SIDE:
			case Boss::CLOUD_VER:
				FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::CLOUD, 9000);
				break;
			case Boss::DARKNESS:
				FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::DARKNESS, 12000);
				break;
			case Boss::INVERSION:
				FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::INVERSION, 9000);
				break;
			}
			pattern = PATTERN::ATTACK;
		}
		break;
	case Boss::ATTACK:
		

		

		switch (nowAction)
		{
		case Boss::CLOUD_SIDE:

			actionCounter -= 0.25f;
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

			actionCounter -= 0.25f;
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
		case Boss::INVERSION:
			inversionLevel = std::clamp(inversionLevel, -1.0f, 1.0f);
			isInversion = true;
		}

		pattern = PATTERN::STAY;

		break;
	case Boss::STAY:
		if (actionCounter > 10.0f)
		{
			FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::BOSSATTACK, 10000);
			pattern = PATTERN::ATTACK_START;
			isAttack = true;
			actionCounter = -10.0f;
			isActionMessage = false;
		}
		else if (!isActionMessage && actionCounter > 8.0f)
		{
			
			isActionMessage = true;
			//ここで抽選を確定させ文字を表示する
			nowAction = nextAction;
			switch (nowAction)
			{
			case Boss::CLOUD_SIDE:
				sentence->SetNextSentence(sentence->BossName() + "の\n灰燼の一線 (スモーク・バレット)");
				break;
			case Boss::CLOUD_VER:
				sentence->SetNextSentence(sentence->BossName() + "の\n灰天落とし (スモーク・フォール)");
				break;
			case Boss::DARKNESS:
				sentence->SetNextSentence(sentence->BossName() + "の\n暗黒領域 冥闇降界 (ダークネス・アビス)");
				break;
			case Boss::INVERSION:
				sentence->SetNextSentence(sentence->BossName() + "の\n反転領域 冥界転位 (インバートワールド)");
				break;
			}
		}
		else
			actionCounter += Time::DeltaTime();

		break;
	case Boss::DAMAGE:
		if (isDamage && flashFrame > 30)
		{
			isDamage = false;
			flashFrame = 0;

			pattern = PATTERN::STAY;
		}
		break;
	case Boss::DEAD:
		if(!isDead)
		{
			sentence->SetNextSentence(sentence->BossName() + "は倒れた");
		}

		if (downCounter > 1.5f)
		{
			sizeY -= downSpeed;
			posY += downSpeed;
			downSpeed++;
		}
		else
			downCounter += Time::DeltaTime();

		isDead = true;

		break;
	}
}

void Boss::Draw()
{
	
	DrawRectRotaGraph(200, 450, 0, 0, 1024, 732, 1.3f * inversionLevel, 0.0f, bookbackimage, true);
	DrawRectRotaGraph(390, 450, 0, 0, 788, 900, 1.05f * inversionLevel, 0.0f, bookimage, true);
	DrawRectRotaGraph(1200, 400, 0, 0, 1024, 1024, 1.0f * inversionLevel, 0.0f, backimage, true);

	float boxLevel = std::clamp(1.0f - inversionLevel, 0.0f, 1.0f);

	DrawRectRotaGraph(410 - boxPos.x * boxLevel, 400 + boxPos.y * boxLevel, 0, 0, 504, 504, 1.2f * inversionLevel, 0.0f, boximage, true);


	//DrawBox(100, 100, 2000, 2000, GetColor(0, 0, 0), TRUE);
	//SetDrawBright(230, 230, 230);
	
	if (isAttack)
	{
		if ((flashFrame / FLASH_INTERVAL) % 2 == 0)
		{
			// 通常描画
			DrawRectRotaGraph(1200, 300, 0, 0, 260, 260, 1.6f * inversionLevel, 0.0f, image, true);
		}
		else
		{
			DrawRectRotaGraph(1200, 300, 0, 0, 260, 260, 1.6f * inversionLevel, 0.0f, whiteimage, true);
		}
	}
	else if (isDamage)
	{

		SetDrawBright(73, 0, 0);
		DrawRectRotaGraph(1200 + damagePos[0].x, 300 + damagePos[0].y, 0, 0, 260, 260, 1.6f * inversionLevel, 0.0f, image, true);

		SetDrawBright(139, 0, 0);
		DrawRectRotaGraph(1200 + damagePos[2].x, 300 + damagePos[2].y, 0, 0, 260, 260, 1.6f * inversionLevel, 0.0f, image, true);

		SetDrawBright(255, 0, 0);
		DrawRectRotaGraph(1200 + damagePos[1].x, 300 + damagePos[1].y, 0, 0, 260, 260, 1.6f * inversionLevel, 0.0f, image, true);
		SetDrawBright(255, 255, 255); // 戻す（重要）
		//if ((flashFrame / FLASH_INTERVAL) % 2 == 0)

	}
	else
		DrawRectRotaGraph(1200, posY, 0, 0, 260, sizeY, 1.6f * inversionLevel, 0.0f, image, true);
	//SetDrawBright(255, 255, 255);

	DrawFormatStringToHandle(
		1300, 200,
		GetColor(0, 0, 0),
		fontOutHandle,
		"%d",
		10 - (int)actionCounter
	);
	DrawFormatStringToHandle(
		1300, 200,
		GetColor(255, 255, 255),
		fontHandle,
		"%d",
		10 - (int)actionCounter
	);

	/*std::string serihu = bossName + "があらわれた！！";

	DrawStringToHandle(
		900, 650,
		serihu.c_str(),
		GetColor(255, 255, 255),
		fontHandle
	);*/
}

void Boss::Damage(int damageNum, float stopnum)
{
	HP -= damageNum;
	hitStop = stopnum;

	if (pattern != PATTERN::STAY)
		return;

	isDamage = true;
	pattern = PATTERN::DAMAGE;
}
