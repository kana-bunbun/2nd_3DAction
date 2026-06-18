#include "TileObject.h"
#include "../../Utility/Color.h"
namespace {
	constexpr Vector3 kFloorSize = { MapConst::kFloorScale,MapConst::kFloorScale ,MapConst::kFloorScale };
}
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
}

void TileObject::ResolveCollision(GameObject& other, const Collision::Result& result)
{}

void TileObject::SetFloorModel(int modelHandle)
{
	m_modelHandle = modelHandle;
	MV1SetScale(m_modelHandle, kFloorSize.ToVECTOR());
	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.1f,0.1f,0.1f,1.0f };
	MV1SetMaterialEmiColor(m_modelHandle, 0, color);
}


