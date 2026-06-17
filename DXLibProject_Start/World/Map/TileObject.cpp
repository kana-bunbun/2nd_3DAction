#include "TileObject.h"
#include "../../Utility/Color.h"

TileObject::TileObject()
{
}

TileObject::~TileObject()
{
	MV1DeleteModel(m_modelHandle);
}

void TileObject::Init()
{

}

void TileObject::End()
{

}

void TileObject::Update(float deltaTime)
{
	DrawSphere3D(m_transform.position.ToVECTOR(), 10, 10, Color::kYellow, Color::kYellow, TRUE);
}

void TileObject::ResolveCollision(GameObject& other, const Collision::Result& result)
{}


