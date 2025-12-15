#pragma once
#include "../Library/gameObject.h"
#include "Tile.h"
#include <vector>
#include "ActionEvent.h"


class TileManager : public GameObject
{
public:
	TileManager();
	~TileManager();

	void Update() override;
	void Draw() override;

	void CreateTiles(int height, int width);
	void DeleteTiles();

	void OnInputTile(Vector2I dir);

	bool IsPerfectCheck();

	ActionEvent<> OnMoveTile;
	ActionEvent<> OnPerfectTile;

private:
	void OnMoveEvent();
	void OnPerfectEvent();
	void MoveRandomTile();

	std::vector<std::vector<Tile*>> tile_list;
	Tile* air_tile;
};