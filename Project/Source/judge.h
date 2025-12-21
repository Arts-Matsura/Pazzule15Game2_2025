#pragma once
#include "../Library/gameObject.h"

class Judge :public GameObject {
public:
	Judge();
	~Judge();
	void Update()override;
	void Draw()override;

	float StartCounter() { return startCounter; }
	float EndCounter() { return endCounter; }
	bool GameStart() { return gameStart; }
	bool GameEnd() { return gameEnd; }

	void EndCountStart() { isEndCount = true; }
	bool ChangeScene() { return changeScene; }
private:

	int image;
	float imageSize;
	float sizeSpeed;

	float startCounter;
	float endCounter;
	bool gameStart;
	bool gameEnd;

	bool isEndCount;

	bool fadeStart;
	bool changeScene;

	bool isEndSound;
};