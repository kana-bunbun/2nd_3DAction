#include "MapTile.h"

MapTile::MapTile(int posX,int posY, int id) :
	m_posX(posX), 
	m_posY(posY), 
	m_id(id),
	m_terrain(eTerrain::Invalid),
	m_squareData(nullptr)
{
	m_squareData = new SquareData(posX, posY, id);
}
