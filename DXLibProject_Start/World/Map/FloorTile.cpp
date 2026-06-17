#include "FloorTile.h"

FloorTile::FloorTile(int ID, Vector3 position)
{
	m_ID = ID;
	m_transform.position = position;
}

FloorTile::~FloorTile()
{}

void FloorTile::ResolveCollision(GameObject & other, const Collision::Result & result)
{}
