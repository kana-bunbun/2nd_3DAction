#pragma once
#include"../../Utility/Vector3.h"
#include"MapConst.h"
// マップの1マスのクラス
class MapTile
{
public:

public:
	MapTile()=default;
	MapTile(Vector3 position, int id) :m_position(position), m_id(id), m_terrain(eTerrain::Invalid) {};
	~MapTile() = default;

	const Vector3 GetPos()const { return m_position; }
	const int GetId()const { return m_id; }
	const void SetTerrain(eTerrain terrain){ m_terrain = terrain; }
private:
	Vector3 m_position;
	int m_id;
	eTerrain m_terrain;
};

