#pragma once
#include"TileObject.h"
class FloorTile:public TileObject
{
public:
	FloorTile(int ID, Vector3 position);
	~FloorTile();

	void ResolveCollision(GameObject& other, const Collision::Result& result);

private:
};

