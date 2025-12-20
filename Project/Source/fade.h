#pragma once
#include "../Library/gameObject.h"

class Fade :public GameObject {
public:
	Fade();
	~Fade();
	void Update()override;
	void Draw()override;

	void FadeInStart(float _time);
	void FadeOutStart(float _time);
	bool FadeEnd() { return isFade; }

	enum STATE {
		FADE_IN = 0,
		FADE_OUT,
		STAY,
	};
private:
	float fadeAlphaLevel;

	float maxTime;
	float time;

	bool isFade;

	STATE state;
};