#include "DOTween.h"
#include <list>
#include "Time.h"

namespace DOTween
{
	struct TweenDef
	{
		Vector3* move_ptr;
		Vector3 start;
		Vector3 target;
		float move_rate;
		float move_time;
		bool need_delete;
	};

	std::list<TweenDef>* tween_list;
}

using namespace DOTween;

void DOTween::Initialize()
{
	tween_list = new std::list<TweenDef>();
}

void DOTween::Release()
{
	SAFE_DELETE(tween_list);
}

void DOTween::Update()
{
	const float delta_time = Time::DeltaTime();

	for (TweenDef& tween : *tween_list)
	{	
		tween.move_rate += delta_time / tween.move_time;
		if (tween.move_rate >= 1.0f)
		{
			*(tween.move_ptr) = tween.target;
			tween.need_delete = true;
			continue;
		}
		
		*(tween.move_ptr) = Vector3::Lerp(tween.start, tween.target, tween.move_rate);
	}

	for (auto itr = tween_list->begin(); itr != tween_list->end();)
	{
		TweenDef& tween = *itr;
		if (tween.need_delete)
		{
			itr = tween_list->erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void DOTween::Move(Vector3* move_ptr, const Vector3& target, float duration)
{
	// 新規追加
	TweenDef tween;
	tween.move_ptr = move_ptr;
	tween.start = *move_ptr;
	tween.target = target;
	tween.move_rate = 0.0f;
	tween.move_time = duration;
	tween.need_delete = false;

	// push
	tween_list->push_back(tween);
}

void DOTween::Destroy(Vector3* move_ptr, bool is_complete)
{
	// 削除フラグのオン
	for (TweenDef& tween : *tween_list)
	{
		if (tween.move_ptr == move_ptr)
		{
			if (is_complete)
			{
				*(tween.move_ptr) = tween.target;
			}
			tween.need_delete = true;
			return;
		}
	}
}

void DOTween::Complete(Vector3* move_ptr)
{
	// 即座に完了させる
	for (TweenDef& tween : *tween_list)
	{
		if (tween.move_ptr == move_ptr)
		{
			*(tween.move_ptr) = tween.target;
			tween.need_delete = true;
			return;
		}
	}
}

bool DOTween::IsMoving(Vector3* move_ptr)
{
	// 移動中かどうか
	for (TweenDef& tween : *tween_list)
	{
		if (tween.move_ptr == move_ptr)
		{
			return true;
		}
	}
	return false;
}
