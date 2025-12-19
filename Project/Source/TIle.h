#pragma once
#include"Transform.h"
#include"../Library/gameObject.h"

class ContextTile
{
private:
	static ContextTile* instance;

	//private
	float tileSize = 128.0f;
public:
	//private
	int hImage = -1;

	//private
	Vector2I imageSize = Vector2I(512, 512);
	//private
	int tileCount = 4;
	//public
	const int IMAGE_MAX = 4;

	//public
	void LoadGraph(int id, int tileCount);

	static ContextTile& Instance()
	{
		if (instance == nullptr)
		{
			instance = new ContextTile();
		}

		return (*instance);
	}
};

class Tile
{
public:
	Tile();
	Tile(int _id);
	~Tile();

	void Draw();

	void SetTile(const Vector2I& _delta, float tileSize);

//private:
	//int hdragon;//ƒhƒ‰ƒSƒ“‚Ì‰æ‘œ
	Transform transform;
	Vector2I delta;	//¡‚Ìƒ}ƒX–Ú
	int id;			//©•ª‚Ì”Ô†
	Vector2I offsetuv;
};