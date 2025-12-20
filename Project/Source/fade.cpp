#include "fade.h"

#include "Screen.h"

#include "../Library/time.h"

Fade::Fade()
{
	isFade = true;
	fadeAlphaLevel = 255.0f;

	maxTime = 0.0f;
	time = 0.0f;

	state = STATE::STAY;
}

Fade::~Fade()
{
}

void Fade::Update()
{
	if (maxTime > time)
		time += Time::DeltaTime();
	else
	{
		isFade = false;
		maxTime = 0.0f;
		time = 0.0f;
		state = STATE::STAY;
	}

	switch (state)
	{
	case Fade::FADE_IN:
		fadeAlphaLevel = 255.0f * (time / maxTime);
		break;
	case Fade::FADE_OUT:
		fadeAlphaLevel = 255.0f - 255.0f * (time / maxTime);
		break;
	}
}

void Fade::Draw()
{
	/*if (!isFade)
		return;*/

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)fadeAlphaLevel);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Fade::FadeInStart(float _time)
{
	if (state != STATE::STAY)
		return;

	isFade = true;
	state = STATE::FADE_IN;
	maxTime = _time;
	time = 0.0f;
}

void Fade::FadeOutStart(float _time)
{
	if (state != STATE::STAY)
		return;

	isFade = true;
	state = STATE::FADE_OUT;
	maxTime = _time;
	time = 0.0f;
}
