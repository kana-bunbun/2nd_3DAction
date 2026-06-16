#include "TileObject.h"

TileObject::TileObject():
	m_modelHandles(),
	m_wallDirections()
{

}

TileObject::~TileObject()
{
	for (auto& model : m_modelHandles) {
		MV1DeleteModel(model);
	}
}

void TileObject::Init()
{

}

void TileObject::End()
{

}

void TileObject::Update(float deltaTime)
{

}

void TileObject::Draw()
{

}
