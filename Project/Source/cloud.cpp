#include "cloud.h"
#include "cloudManager.h"

#include "../Library/time.h"

Cloud::Cloud()
{
	isCloud = false;
	survivalTime = 0.0f;

	isCreate = false;
	isDelete = false;
}

Cloud::~Cloud()
{
}

void Cloud::Update()
{
	if (survivalTime > 0.0f)
		survivalTime -= Time::DeltaTime();
	else
		isCloud = false;

}

void Cloud::Draw(int x, int y)
{
	if (isCloud)
		DrawRectRotaGraph(100 + x * (496 / 4.0f), 100 + y * (556 / 4.0f), 0, 0, 496, 556, 0.25f, 0.0f, FindGameObject<CloudManager>()->CloudImage(), true);
}

void Cloud::CreateEffect()
{
	isCreate = true;
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

