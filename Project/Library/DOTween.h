#pragma once
#include "myDxLib.h"
#include "../Source/Transform.h"

namespace DOTween
{	
	void Initialize();
	void Release();
	void Update();
	
	void Move(Vector3* move_ptr, const Vector3& target, float duration);
	void Destroy(Vector3* move_ptr, bool is_complete = false);
	void Complete(Vector3* move_ptr);

	bool IsMoving(Vector3* move_ptr);
};