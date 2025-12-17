#pragma once
#include "../Library/gameObject.h"

class Darkness :public GameObject {
public:
	Darkness();
	~Darkness();
	void Update()override;
	void Draw()override;

	void EffectStart();
	void EffectEnd();
private:

	int alphaLevel;
	int circleImage;

	//生成時間
	float counter; //10秒カウント（生成時間）
	bool isCounte; //カウント開始するか（生成時間）

	bool isStart;
	bool isEndStart;
	bool isDarkness;
	float circleCounter;
};