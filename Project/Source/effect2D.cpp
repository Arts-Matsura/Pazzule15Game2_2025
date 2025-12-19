#include "effect2D.h"

#include "../Library/resourceLoader.h"

Effect2D::Effect2D()
{
	frame = 0;

	//-TYPE_01----------------------------------------
	effects[0].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_01.png");
	effects[0].pos.x = 0.0f;
	effects[0].pos.y = 0.0f;
	effects[0].maxframe = 10;
	effects[0].maxTime = 0;
	effects[0].isActive = false;

	effects[1].image = ResourceLoader::LoadGraph("data\\2D\\spritesheet_02.png");
	effects[1].pos.x = 0.0f;
	effects[1].pos.y = 0.0f;
	effects[1].maxframe = 9;
	effects[1].maxTime = 0;
	effects[1].isActive = false;
	//------------------------------------------------
}

Effect2D::~Effect2D()
{
}

void Effect2D::Update()
{
	//maxTime*60
}

void Effect2D::Draw()
{
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
