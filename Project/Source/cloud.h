#pragma once
#include "../Library/gameObject.h"
#include <vector>

class Cloud :public GameObject {
public:
	Cloud();
	~Cloud();
	void Update()override;
	void Draw(int x,int y);

	void CreateEffect();
	void UpdateCreateEffect();

	void DeleteEffect();
	void UpdateDeleteEffect();

	bool isCloud;
	float survivalTime;

private:

	bool isCreate;
	bool isDelete;

	float efFrame; //エフェクトの時間

	int alphaLevel;
};
