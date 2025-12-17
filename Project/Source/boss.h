#pragma once
#include "../Library/gameObject.h"

#include "cloudManager.h"
#include "darkness.h"

class Boss :public GameObject {
public:
	Boss();
	~Boss();
	void Update()override;
	void Draw()override;

private:

	enum ACTION {
		CLOUD_SIDE = 0,
		CLOUD_VER,
		DARKNESS,
		ACTION_MAX
	};

	float actionCounter;

	int image;
	int backimage;
	int bookimage;
	int bookbackimage;
	int boximage;

	std::string bossName;

	int fontHandle;

	CloudManager* cloud;
	Darkness* darkness;
};