#pragma once
#include"../Component/Transform.h"
#include"../../Utility/Vector3.h"
#include<memory>
#include<vector>
class TileObject;
class Stair;
class TileManager
{
public:
	TileManager();
	~TileManager();

	void Draw();
	void DrawMiniMap();
	bool InDevideList(size_t id);
	void DrawMark();
	void SetMarkPos(Transform markPos) { m_markPos = markPos; }

	int RandomPassableID();
	int RandomRoomID();

private:
	Transform m_markPos;
	int m_cursorHandle;
	std::vector<std::unique_ptr<TileObject>> m_pTiles;
	int m_floorHandle;
	int m_wallHandle;
	std::unique_ptr<Stair>stair;
};

