#include "cloud.h"
#include "cloudManager.h"

#include "../Library/time.h"

Cloud::Cloud()
{
	isCloud = false;
	survivalTime = 0.0f;

	isCreate = false;
	isDelete = false;

	efFrame = 0.0f;

	alphaLevel = 255;
}

Cloud::~Cloud()
{
}

void Cloud::Update()
{
	if (efFrame > 0.0f)
	{
		efFrame -= Time::DeltaTime();
		return;
	}

	if (survivalTime > 0.0f)
		survivalTime -= Time::DeltaTime();
	else
	{
		if (alphaLevel > 0 && isCloud)
			alphaLevel -= 17;
		else
			isCloud = false;
	}

}

void Cloud::Draw(int x, int y)
{
	if (isCloud && efFrame <= 0.0f)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaLevel);
		DrawRectRotaGraph(200 + x * (556 / 4.0f), 200 + y * (556 / 4.0f), 0, 0, 496, 556, 0.35f, 0.0f, FindGameObject<CloudManager>()->CloudImage(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Cloud::CreateEffect()
{
	isCreate = true;
	efFrame = 0.25f;
}

void Cloud::UpdateCreateEffect()
{
	if (!isCreate)
		return;
}

void Cloud::DeleteEffect()
{
	isDelete = true;
}

void Cloud::UpdateDeleteEffect()
{
	if (!isDelete)
		return;
}

