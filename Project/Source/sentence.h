#pragma once
#include "../Library/gameObject.h"

class Sentence :public GameObject {
public:
	Sentence(int num);
	~Sentence();
	void Update()override;
	void Draw()override;

	void SetNextSentence(std::string next);
	std::string BossName() { return bossName; }

private:

	enum STATE {
		NOW_UP = 0,
		NEXT_START,
		NOW_CHANGE,
	};

	STATE state;

	int charCount;
	int frame;
	int byte;

	bool isAction;

	Vector2 nowPos, nextPos;

	std::string bossName;

	std::string nowSentence;
	std::string nextSentence;

	int fontHandle;

};