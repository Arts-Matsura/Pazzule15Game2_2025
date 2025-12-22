#include "TIle.h"
#include "Renderer2D.h"
#include<assert.h>
#include "../Library/resourceLoader.h"
#include "../library/DOTween.h"

ContextTile* ContextTile::instance = nullptr;

namespace
{
	static const Vector2 BasePosition = Vector2(-580.0f, -240.0f);
}

Tile::Tile() : Tile(0) {}
Tile::Tile(int _id)
{
	id = _id;
	//hImage = _hImage;
	//drawsize = Vector2I(512,512);
	int cnt = ContextTile::Instance().tileCount;
	offsetuv = Vector2I(id % cnt, id / cnt) * (ContextTile::Instance().imageSize.x / cnt);
}

Tile::~Tile()
{
}

void Tile::SetTile(const Vector2I& _delta, float tileSize)
{
	delta = _delta;
	Vector3 next = Vector3(_delta.x, _delta.y, 0.0f) * (ContextTile::Instance().imageSize.x / ContextTile::Instance().tileCount);
	if (DOTween::IsMoving(&transform.position))
	{
		transform.position = next;
	}
	else
	{
		//DOTween::Move(&transform.position, next, 0.1f);
		transform.position = next;
	}
}

void Tile::Draw()
{
	if (transform.is_active)
	{
		Vector2 pos = Vector2(transform.position + transform.scale) + BasePosition;
		if (id == 15)
		{
			Renderer::RectGraph(pos, Vector2I::Zero(), Vector2I(128, 128), ContextTile::Instance().hMove);
		}
		else
		{
			Renderer::RectGraph(pos, offsetuv, ContextTile::Instance().imageSize / ContextTile::Instance().tileCount, ContextTile::Instance().hImage);
		}

		// ID•\Ž¦
		if (false)//Œã‚Å‹A‚é‚©‚à
		{
			Renderer::Text(pos, Color::Magenta(), std::to_string(id));
		}
	}
}

void ContextTile::LoadGraph(int id, int tileCount)
{
	// “¯‚¶‰æ‘œID‚È‚ç‚¸‚ç‚·
	if (ContextTile::prevId == id)
	{
		id = (id + 1) % IMAGE_MAX;
	}

	ContextTile::prevId = id;

	int& hImage = ContextTile::hImage;
	if (hImage <= 0)
	{
		DeleteGraph(hImage);
		hImage = -1;
	}

	// Load
	static const std::string path = "data/2D/sheet_";
	hImage = ResourceLoader::LoadGraph(path + std::to_string(id) + ".png");
	assert(hImage >= 0);

	ContextTile::imageSize = GetGraphSize(hImage);
	ContextTile::tileCount = tileCount;
	ContextTile::tileSize = ContextTile::imageSize.x / static_cast<float>(tileCount);

	if (ContextTile::hMove <= 0)
	{
		ContextTile::hMove = ResourceLoader::LoadGraph("data/2D/move_dir.png");
	}
}
