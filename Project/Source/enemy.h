#pragma once
#include"../Library/gameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Update()override;
	void Draw()override;
private:
	int hImage;
};