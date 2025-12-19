#include "cloudManager.h"

CloudManager::CloudManager()
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		for (int j = 0; j < LINE_MAX; j++)
		{
			clouds[i][j] = new Cloud;
			clouds[i][j]->isCloud = false;
			
		}
	}
	/*CreateSide(1);
	CreateSide(3);
	CreateVer(0);
	CreateVer(2);*/
	

	cloudImage = LoadGraph("data\\2D\\Cloud.png");

	isEffect = false;
	effectAlphaLevel = 155;
	size = 1.0f;
	state = STATE::BIGGER;
}

CloudManager::~CloudManager()
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		for (int j = 0; j < LINE_MAX; j++)
		{
			delete clouds[i][j];
		}
	}
}

void CloudManager::Update()
{
	float biggerRate = 0;
	if (1.5 - size > 0.0f)
		biggerRate = (0.5f / (1.5 - size)) - 1.0f;
	else
		biggerRate = 1.0f;


	if (isEffect)
	{
		switch (state)
		{
		case CloudManager::BIGGER:
			if (size < 1.5)
				size += 0.025f;
			else
			{
				size = 1.5f;
				state = STATE::SMALLER;
			}

			effectAlphaLevel = 100 * biggerRate + 155;
			break;
		case CloudManager::SMALLER:
			if (size > 1.2)
				size -= 0.04f;
			else
			{
				size = 1.2f;
				state = STATE::FINISH;
			}

			effectAlphaLevel -= 10;
			break;
		case CloudManager::FINISH:
			effectAlphaLevel -= 10;

			if (effectAlphaLevel <= 0)
				isEffect = false;
			break;
		}
	}
}

void CloudManager::Draw()
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		for (int j = 0; j < LINE_MAX; j++)
		{
			clouds[i][j]->Draw(i, j);
		}
	}
	
	if (isEffect)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, effectAlphaLevel);
		DrawRectRotaGraph(410, 400, 0, 0, 496, 556, size, 0.0f, cloudImage, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void CloudManager::Create(int MaxBoard, int sideNum, int verNum)
{
}

void CloudManager::CreateVer(int Num)
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		clouds[Num][i]->isCloud = true;
		clouds[Num][i]->survivalTime = 10.0f;
		clouds[Num][i]->CreateEffect();
	}

	if (!isEffect)
	{
		isEffect = true;
		effectAlphaLevel = 155;
		size = 1.0f;
		state = STATE::BIGGER;
	}
}

void CloudManager::CreateSide(int Num)
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		clouds[i][Num]->isCloud = true;
		clouds[i][Num]->survivalTime = 10.0f;
		clouds[i][Num]->CreateEffect();
	}

	if (!isEffect)
	{
		isEffect = true;
		effectAlphaLevel = 155;
		size = 1.0f;
		state = STATE::BIGGER;
	}
}

void CloudManager::DeleteCloud()
{

}
