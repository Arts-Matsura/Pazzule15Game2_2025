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

	//-TYPE_02----------------------------------------
	effects[2].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_explosion_01.png");
	effects[2].pos.x = 0.0f;
	effects[2].pos.y = 0.0f;
	effects[2].size = 0;
	effects[2].sizeMax.x = 96;
	effects[2].sizeMax.y = 96;
	effects[2].maxframe = 9;
	effects[2].maxTime = -1;
	effects[2].isActive = false;
	effects[2].time = 0;

	effects[3].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_explosion_02.png");
	effects[3].pos.x = 0.0f;
	effects[3].pos.y = 0.0f;
	effects[3].size = 0;
	effects[3].sizeMax.x = 128;
	effects[3].sizeMax.y = 128;
	effects[3].maxframe = 13;
	effects[3].maxTime = -1;
	effects[3].isActive = false;
	effects[3].time = 0;

	effects[4].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_explosion_03.png");
	effects[4].pos.x = 0.0f;
	effects[4].pos.y = 0.0f;
	effects[4].size = 0;
	effects[4].sizeMax.x = 48;
	effects[4].sizeMax.y = 48;
	effects[4].maxframe = 10;
	effects[4].maxTime = -1;
	effects[4].isActive = false;
	effects[4].time = 0;
	//------------------------------------------------

	//-TYPE_03----------------------------------------
	effects[8].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_Circle_01.png");
	effects[8].pos.x = 0.0f;
	effects[8].pos.y = 0.0f;
	effects[8].size = 0;
	effects[8].sizeMax.x = 96;
	effects[8].sizeMax.y = 96;
	effects[8].maxframe = 10;
	effects[8].maxTime = -1;
	effects[8].isActive = false;
	effects[8].time = 0;

	effects[6].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_Circle_02.png");
	effects[6].pos.x = 0.0f;
	effects[6].pos.y = 0.0f;
	effects[6].size = 0;
	effects[6].sizeMax.x = 96;
	effects[6].sizeMax.y = 96;
	effects[6].maxframe = 7;
	effects[6].maxTime = -1;
	effects[6].isActive = false;
	effects[6].time = 0;

	effects[7].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_Circle_03.png");
	effects[7].pos.x = 0.0f;
	effects[7].pos.y = 0.0f;
	effects[7].size = 0;
	effects[7].sizeMax.x = 96;
	effects[7].sizeMax.y = 96;
	effects[7].maxframe = 8;
	effects[7].maxTime = -1;
	effects[7].isActive = false;
	effects[7].time = 0;

	effects[5].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_Circle_04.png");
	effects[5].pos.x = 0.0f;
	effects[5].pos.y = 0.0f;
	effects[5].size = 0;
	effects[5].sizeMax.x = 96;
	effects[5].sizeMax.y = 96;
	effects[5].maxframe = 10;
	effects[5].maxTime = -1;
	effects[5].isActive = false;
	effects[5].time = 0;
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
		for (int i = 2; i < 5; i++)
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
	case Effect2D::TYPE_03:
		for (int i = 5; i < EFFECT_MAX; i++)
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
	}
}
