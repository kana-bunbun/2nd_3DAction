#pragma once
#include"../../Utility/Vector3.h"
#include"MapConst.h"
#include"SquareData.h"
// マップの1マスのクラス
class MapTile
{
public:

public:
	MapTile()=default;
	MapTile(int posX,int posY, int id) ;
	~MapTile() = default;

	const int GetPosX()const { return m_posX; }
	const int GetPosY()const { return m_posY; }
	const int GetId()const { return m_id; }
	const void SetTerrain(eTerrain terrain) { m_terrain = terrain; m_squareData->SetTerrain(terrain); }
	void SetRoomId(int id) { m_squareData->SetRoomID(id); }
	SquareData* GetSquareData() { return m_squareData; }
private:
	int m_posX;
	int m_posY;
	int m_id;
	eTerrain m_terrain;
	SquareData* m_squareData;
};

