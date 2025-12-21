#pragma once
#include "../Library/gameObject.h"

namespace {
	static const int EFFECT_MAX = 9;
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
		int image; //‰æ‘œ
		int maxframe; //‰æ‘œ‚Ì–‡”
		Vector2 pos; //À•W
		int size; //•`‰æ‚µ‚Ä‚¢‚éêŠ
		Vector2 sizeMax; //•`‰æ”ÍˆÍ
		int maxTime; //Ä¶ŠÔ
		bool isActive; //“®‚¢‚Ä‚¢‚é‚©
		int time;
	};
	Effects effects[EFFECT_MAX];

	
};