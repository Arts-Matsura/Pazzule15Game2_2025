#pragma once
#include "../Library/sceneBase.h"
#include "sound.h"
#include "fade.h"

class PlayScene : public 
	SceneBase {
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int hShadow; // シャドウバッファのハンドラ

	Sound* sound;
	Fade* fade;
};