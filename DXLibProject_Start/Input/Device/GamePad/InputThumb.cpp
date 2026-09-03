#include "InputThumb.h"
#include"Utility/MyMath.h"
namespace {
	// スティックの最大入力値
	constexpr int kThumbInputMax = 32767;
	// スティックの入力を無視する割合
	constexpr float kThumbDeadZone = 0.2f;
	// スティックの最小入力値
	constexpr float kThumbInputMin = kThumbInputMax* kThumbDeadZone;
	// スティックの最小入力値の2乗
	constexpr float kThumbInputSqMin = kThumbInputMin * kThumbInputMin;

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
	Vector2 inputVector = Vector2::zero;
	float inputRadian = 0.0f;
	float inputRatio = 0.0f;
	if (holizontal)
	{
		// 水平方向の入力があれば入力割合を取得
		inputVector.x = MyMath::Clamp(static_cast<float>(holizontal) / static_cast<float>(kThumbInputMax), -1.0f, 1.0f);
	}
	if (vertical)
	{
		// 垂直方向の入力があれば入力割合を取得
		inputVector.y = MyMath::Clamp(static_cast<float>(vertical) / static_cast<float>(kThumbInputMax), -1.0f, 1.0f);
	}
	// 入力角度を求める
	inputRadian = atan2(inputVector.x, inputVector.y);
	// 入力があれば入力量を計算
	if (inputVector.GetSqLength() > kThumbDeadZone) {
		{
			// 4方向の入力方向を取得
			m_thumbData.directionFour = MyMath::RadianToDirectionFour(inputRadian);
			// 8方向の入力方向を取得
			m_thumbData.directionEight = MyMath::RadianToDirectionEight(inputRadian);
			inputRatio = MyMath::Clamp(inputVector.GetLength(), 0.0f, 1.0f);
		}
	}


			m_thumbData.vectorState = VectorState(inputVector, inputRadian, inputRatio);
			return;
}
