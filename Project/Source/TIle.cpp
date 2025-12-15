#include "TIle.h"
#include "Renderer2D.h"
#include<assert.h>

Tile::Tile() : Tile(0)
{
	
}

Tile::Tile(int _id)
{
	id = _id;
	//ドラゴンの画像の初期化
	hdragon = LoadGraph("data\\2D\\cute_dragon.png");
	assert(hdragon);
	drawsize = Vector2I(512,512);
	offsetuv = Vector2I(id % 4, id / 4) * (512 / 4);
}

Tile::~Tile()
{
	//ドラゴンの画像のハンドルの削除
	DeleteGraph(hdragon);
}

void Tile::SetTile(const Vector2I& _delta, float tileSize)
{
	delta = _delta;
	//transform.position = Vector3(_delta.x, _delta.y, 0.0f) * tileSize;
	 transform.position = Vector3(_delta.x, _delta.y, 0.0f) * (512 /4);
	//transform.scale = Vector3(tileSize, tileSize, 1.0f) / 2.0f;
}

void Tile::Draw()
{
	if (transform.is_active)
	{
		Vector2 pos = Vector2(transform.position + transform.scale);
		Renderer::RectGraph(pos, offsetuv, Vector2I(512, 512) / 4, hdragon);
		Renderer::Text(pos, Color::Magenta(), std::to_string(id));
	}
}
