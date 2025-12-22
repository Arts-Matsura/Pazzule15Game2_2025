#include "control.h"

Control::Control()
{
	prevPushed = false;
	OnInputEvent += [this](Vector2I dir) { OnKeyPush(dir); };
}

Control::~Control()
{
}

void Control::Update()
{
	UpdateInput();
}

void Control::Draw()
{

}

void Control::UpdateInput()
{
	// キー入力の更新（方向は -1 / 0 / +1）
	currentKey.y = CheckHitKey(KEY_INPUT_W) - CheckHitKey(KEY_INPUT_S);
	currentKey.x = CheckHitKey(KEY_INPUT_A) - CheckHitKey(KEY_INPUT_D);

	// 押されているか判定
	if (currentKey.x != 0 || currentKey.y != 0)
	{
		// ななめ入力を完全に無効化
		if (currentKey.x != 0 && currentKey.y != 0)
		{
			DebugLog("斜め入力はできません"); //ここ
			prevPushed = true; // 状態だけ更新
			return;
		}

		// 押された瞬間のみ処理
		if (!prevPushed)
		{
			OnInputEvent.Invoke(currentKey);
		}

		prevPushed = true;
	}
	else
	{
		prevPushed = false;
	}
}



void Control::OnKeyPush(Vector2I dir)
{
	std::string msg =
		"dir.x = " + std::to_string(dir.x) +
		", dir.y = " + std::to_string(dir.y);

	DebugLog(msg.c_str());
}