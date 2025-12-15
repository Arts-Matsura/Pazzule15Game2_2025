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
	CreateSide(1);
	CreateSide(3);
	CreateVer(0);
	CreateVer(2);
	

	cloudImage = LoadGraph("data\\2D\\Cloud.png");
}

CloudManager::~CloudManager()
{
}

void CloudManager::Update()
{
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
}

void CloudManager::CreateSide(int Num)
{
	for (int i = 0; i < LINE_MAX; i++)
	{
		clouds[i][Num]->isCloud = true;
		clouds[i][Num]->survivalTime = 10.0f;
		clouds[i][Num]->CreateEffect();
	}
}

void CloudManager::DeleteCloud()
{

}
