#pragma once
#include "../Library/gameObject.h"
#include <vector>

#include "cloud.h"

namespace {
	static const int LINE_MAX = 4;
}

class CloudManager :public GameObject {
public:
	CloudManager();
	~CloudManager();
	void Update()override;
	void Draw()override;

	void Create(int MaxBoard, int sideNum, int verNum);
	void CreateVer(int Num);
	void CreateSide(int Num);

	void DeleteCloud();

	int CloudImage(){ return cloudImage; }
private:
	Cloud* clouds[LINE_MAX][LINE_MAX];
	int cloudImage;
};
