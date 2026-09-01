#include "InputThumb.h"
#include"Utility/MyMath.h"
namespace {
	// スティックの最大入力値
	constexpr int kThumbInputMax = 32767;

	// 角度計算用の定数
	constexpr float kDirectonFourCalculateValue = 45.0f * MyMath::ToRadian;
	constexpr float kDirectonEightCalculateValue = kDirectonFourCalculateValue * 0.5f;
}

InputThumb::InputThumb():
m_thumbData()
{}

InputThumb::InputThumb(int holizontal, int vertical) :
	m_thumbData()
{
	if (holizontal)
	{
		// 水平方向の入力があれば入力割合を取得
		m_thumbData.vectorState.vector.x = MyMath::Clamp(static_cast<float>(holizontal) / static_cast<float>(kThumbInputMax), -1.0f, 1.0f);
	}
	if (vertical)
	{
		// 垂直方向の入力があれば入力割合を取得
		m_thumbData.vectorState.vector.y = MyMath::Clamp(static_cast<float>(vertical) / static_cast<float>(kThumbInputMax), -1.0f, 1.0f);
	}
	// 入力角度を求める
	m_thumbData.vectorState.radian = atan2(m_thumbData.vectorState.vector.y, m_thumbData.vectorState.vector.x);
	// 入力があれば入力量を計算
	if (m_thumbData.vectorState.vector.GetSqLength() < MyMath::Epsilon) {
		{
			m_thumbData.vectorState.vector = Vector2::Zero;
			m_thumbData.vectorState.radian = 0.0f;
			m_thumbData.vectorState.ratio = 0.0f;
			return;
		} }

	// 4方向の入力方向を取得
	m_thumbData.directionFour = MyMath::RadianToDirectionFour(m_thumbData.vectorState.radian);
	// 8方向の入力方向を取得
	m_thumbData.directionEight = MyMath::RadianToDirectionEight(m_thumbData.vectorState.radian);
	m_thumbData.vectorState.ratio= m_thumbData.vectorState.vector.GetLength() / static_cast<float>(kThumbInputMax);
}
