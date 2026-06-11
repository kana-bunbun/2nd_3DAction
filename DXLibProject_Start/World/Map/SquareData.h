#pragma once
#include"MapConst.h"
#include"RoomData.h"
class SquareData
{
public:
	SquareData(int id, int posX, int posY):m_id(id),m_posX(posX),m_posY(posY),m_roomId(-1),m_terrain(MapConst::eTerrain::Invalid){}

	void SetId(int id) { m_id = id; }
	int GetID() { return m_id; }
	void SetPosX(int posX) { m_posX = posX; }
	void SetPosY(int posY) { m_posY = posY; }

	int GetPosX() { return m_posX; }
	int GetPosY() { return m_posY; }

	void SetTerrain(MapConst::eTerrain terrain) { m_terrain = terrain; }
	MapConst::eTerrain GetTerrain() { return m_terrain; }
	void SetRoomID(int id) { m_roomId = id; }
private:
	MapConst::eTerrain m_terrain;
	int m_id;
	int m_posX;
	int m_posY;
	int m_roomId;
};

