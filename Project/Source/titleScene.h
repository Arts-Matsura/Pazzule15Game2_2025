#pragma once
#include "../Library/sceneBase.h"
#include "sound.h"
#include "fade.h"
/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:

	int image;
	int rogoImage;
	int keyImage;

	float imagePosX, imagePosY;
	float moveX, moveY;

	float sizeFrame;

	Sound* sound;
	Fade* fade;

	bool isPushKey;
};