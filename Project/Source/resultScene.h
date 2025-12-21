#pragma once
#include "../Library/sceneBase.h"
#include "sound.h"
#include "fade.h"

class ResultScene :public SceneBase {
public:
	ResultScene();
	~ResultScene();
	void Update()override;
	void Draw()override;

private:
	int image;
	bool isPushKey;

	int fontHandle;

	Sound* sound;
	Fade* fade;
};