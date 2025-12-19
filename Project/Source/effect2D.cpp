#include "effect2D.h"

#include "../Library/resourceLoader.h"

Effect2D::Effect2D()
{
	//-TYPE_01----------------------------------------
	effects[0].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_01.png");
	effects[0].pos.x = 0.0f;
	effects[0].pos.y = 0.0f;
	effects[0].size = 0;
	effects[0].sizeMax.x = 96;
	effects[0].sizeMax.y = 96;
	effects[0].maxframe = 10;
	effects[0].maxTime = -1;
	effects[0].isActive = false;
	effects[0].time = 0;

	effects[1].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_02.png");
	effects[1].pos.x = 0.0f;
	effects[1].pos.y = 0.0f;
	effects[1].size = 0;
	effects[1].sizeMax.x = 64;
	effects[1].sizeMax.y = 64;
	effects[1].maxframe = 9;
	effects[1].maxTime = -1;
	effects[1].isActive = false;
	effects[1].time = 0;
	//------------------------------------------------
}

Effect2D::~Effect2D()
{
}

void Effect2D::Update()
{
	//maxframe*60/maxtimeÇ…éüÇÃâÊëúÇ…à⁄çs
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!effects[i].isActive)
			continue;
		if (effects[i].maxTime <= 0)
			continue;

		effects[i].time++;
		int frameInterval = effects[i].maxTime / effects[i].maxframe;

		if (effects[i].time >= frameInterval)
		{
			effects[i].time = 0;
			effects[i].size++;

			if (effects[i].size >= effects[i].maxframe)
			{
				effects[i].size = 0;
				effects[i].isActive = false;
			}
		}
	}
	
}

void Effect2D::Draw()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (effects[i].isActive)
			DrawRectRotaGraph((int)effects[i].pos.x, (int)effects[i].pos.y, (int)effects[i].sizeMax.x * effects[i].size, 0, (int)effects[i].sizeMax.x, (int)effects[i].sizeMax.y,
				5.0f, 0.0f, effects[i].image, true);
	}
}

void Effect2D::SetEffect(TYPE _type, Vector2 _pos, int _time)
{
	switch (_type)
	{
	case Effect2D::TYPE_01:
		for (int i = 0; i < 2; i++)
		{
			if (!effects[i].isActive)
			{
				effects[i].pos = _pos;
				effects[i].maxTime = _time;
				effects[i].size = 0;
				effects[i].time = 0;
				effects[i].isActive = true;
			}
		}
		
		break;
	case Effect2D::TYPE_02:
		break;
	case Effect2D::TYPE_03:
		break;
	}
}
