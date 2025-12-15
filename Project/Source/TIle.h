#pragma once
#include"Transform.h"
#include"../Library/gameObject.h"

class Tile
{
public:
	Tile();
	Tile(int _id);
	~Tile();

	void Draw();

	void SetTile(const Vector2I& _delta, float tileSize);

//private:
	int hdragon;//ƒhƒ‰ƒSƒ“‚Ì‰æ‘œ
	Transform transform;
	Vector2I delta;	//¡‚Ìƒ}ƒX–Ú
	int id;			//©•ª‚Ì”Ô†
	Vector2I offsetuv;
	Vector2I drawsize;

};