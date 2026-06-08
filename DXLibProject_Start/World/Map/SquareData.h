#pragma once
#include"MapConst.h"
#include"RoomData.h"
class SquareData
{
public:
	SquareData(int id, int posX, int posY):m_id(id),m_posX(posX),m_posY(posY),m_roomId(-1),m_terrain(eTerrain::Invalid){}

	void SetId(int id) { m_id = id; }
	void SetPosX(int posX) { m_posX = posX; }
	void SetPosY(int posY) { m_posY = posY; }

	void SetTerrain(eTerrain terrain) { m_terrain = terrain; }
	void SetRoomID(int id) { m_roomId = id; }
private:
	eTerrain m_terrain;
	int m_id;
	int m_posX;
	int m_posY;
	int m_roomId;
};

