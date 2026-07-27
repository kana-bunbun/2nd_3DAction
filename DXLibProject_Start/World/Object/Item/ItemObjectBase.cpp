#include "ItemObjectBase.h"
#include "../../../Utility/MyRandom.h"
namespace {
	// 回転速度の最大値
	constexpr float kRotateSpeedMax = DX_PI_F * 2;
}
void ItemObjectBase::RandomRotate()
{
	m_rotateSpeed.x = MyRandom::Float(-kRotateSpeedMax, kRotateSpeedMax);
	m_rotateSpeed.y = MyRandom::Float(-kRotateSpeedMax, kRotateSpeedMax);
	m_rotateSpeed.z = MyRandom::Float(-kRotateSpeedMax, kRotateSpeedMax);
}
