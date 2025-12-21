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

	Sound* sound;
	Fade* fade;
};