#pragma once
#include "../Library/gameObject.h"

namespace {
	static const int EFFECT_MAX = 2;
}

class Effect2D :public GameObject {
public:
	Effect2D();
	~Effect2D();
	void Update()override;
	void Draw()override;

	enum TYPE {
		TYPE_01 = 0,
		TYPE_02,
		TYPE_03,
		TYPE_MAX
	};

	void SetEffect(TYPE _type, Vector2 _pos, int time);
private:

	struct Effects {
		int image;
		int maxframe;
		Vector2 pos;
		int maxTime;
		bool isActive;
	};
	Effects effects[EFFECT_MAX];

	int frame;
};