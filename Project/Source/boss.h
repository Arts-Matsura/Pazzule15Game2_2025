#pragma once
#include "../Library/gameObject.h"

#include "cloudManager.h"
#include "darkness.h"
#include "sentence.h"

class Boss :public GameObject {
public:
	Boss();
	~Boss();
	void Update()override;
	void Draw()override;

	void Damage(int damageNum);

private:

	enum ACTION {
		CLOUD_SIDE = 0,
		CLOUD_VER,
		DARKNESS,
		ACTION_MAX
	};
	ACTION nowAction;
	bool isActionMessage;

	enum PATTERN {
		ATTACK_START = 0, //攻撃前の演出文字とか点滅
		ATTACK, //攻撃
		STAY, //待機時間
		DAMAGE //ダメージの演出
	};
	PATTERN pattern;

	float actionCounter;

	int image;
	int whiteimage;
	int backimage;
	int bookimage;
	int bookbackimage;
	int boximage;

	std::string bossName;

	int fontHandle;

	CloudManager* cloud;
	Darkness* darkness;
	Sentence* sentence;

	bool isAttack; //攻撃するかしないか（攻撃前の点滅で使用）
	bool isDamage; //攻撃を受けたか受けてないか（ダメージ演出に使用）
	int flashFrame; //boss本体演出に使用

	int HP;//最大は5を予定　大：4ダメージ　中：２ダメージ　小：１ダメージ予定

	Vector2 damagePos[3];
};