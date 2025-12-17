#include "darkness.h"

#include "../Library/gameObject.h"

Darkness::Darkness()
{
	isStart = false;
	isEndStart = false;
	isDarkness = false;
	circleCounter = 0.0f;
	alphaLevel = 255;

	counter = 0.0f;
	isCounte = false;
}

Darkness::~Darkness()
{
}

void Darkness::Update()
{
	if (CheckHitKey(KEY_INPUT_K))
		EffectStart();
	else if (CheckHitKey(KEY_INPUT_N))
		EffectEnd();

	if (isStart)
	{
		circleCounter += 0.05f;
		if (circleCounter >= DX_PI_F / 2.0f)
			isDarkness = true;

		if (circleCounter >= DX_PI_F)
		{
			circleCounter = DX_PI_F;
			isStart = false;
			isCounte = true;
		}
	}

	if (isEndStart)
	{
		alphaLevel -= 8.0f;
		if(alphaLevel<=0.0f)
		{
			isStart = false;
			isEndStart = false;
			isDarkness = false;
			circleCounter = 0.0f;
			alphaLevel = 255;

			isCounte = false;
			counter = 0.0f;
		}
	}

	if (isCounte)
	{
		counter += Time::DeltaTime();
		if (counter > 10.0f)
			EffectEnd();
	}
}

void Darkness::Draw()
{
	DrawCircle(1200, 300, 2000.0f * sinf(circleCounter), GetColor(0, 0, 0), true);

	if (!isDarkness)
		return;

	//マウス座標取得
	int mx, my;
	GetMousePoint(&mx, &my);

	int radius = 80; // 四角の半径

	//黒く隠したいエリア範囲
	int areaL = 105;
	int areaT = 97;
	int areaR = 712;
	int areaB = 702;

	//範囲外対策：マウスがエリア外にあるとき描画しないように
	mx = max(areaL + radius, min(mx, areaR - radius));
	my = max(areaT + radius, min(my, areaB - radius));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaLevel);

	// 上
	DrawBox(areaL, areaT,
		areaR, my - radius,
		GetColor(0, 0, 0), TRUE);

	// 下
	DrawBox(areaL, my + radius,
		areaR, areaB,
		GetColor(0, 0, 0), TRUE);

	// 左
	DrawBox(areaL, my - radius,
		mx - radius, my + radius,
		GetColor(0, 0, 0), TRUE);

	// 右
	DrawBox(mx + radius, my - radius,
		areaR, my + radius,
		GetColor(0, 0, 0), TRUE);

	//DrawGraph(mx - 100, my - 100, lightCircleImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Darkness::EffectStart()
{
	if (circleCounter >= DX_PI_F)
		return;

	isStart = true;
}

void Darkness::EffectEnd()
{
	if (circleCounter < DX_PI_F)
		return;


	isEndStart = true;
}
