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

void ItemObjectBase::IntervalUpdate(float deltaTime)
{
	// インターバルのクラスを所持していれば更新処理
	if (!m_pInterval)return;
	m_pInterval->Update(deltaTime);
	if (!m_pActionEffect)return;
	// 効果発動可能なら
	if (m_pInterval->IsExecute()) {
		// 効果の発動処理
		m_pActionEffect->Execute(m_pEffectCollision.get());
		m_pInterval->Execute();
	}
	// 発動効果が終了したら
	if (m_pInterval->IsFinish()) {
		// 自身を非アクティブに設定
		SetActive(false);
	}
}
