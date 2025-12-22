#pragma once
#include "../Library/gameObject.h"

class Back :public GameObject {
public:
	Back();
	~Back();
	void Update()override;
	void Draw()override;

private:
	int bookimage;
	int bookbackimage;
	int boximage;
	int backbackimage;
};