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
	tilt(Vector2::Zero),
	tiltRadian(0.0f),
	tiltRatio(0.0f)
{}

InputThumb::InputThumb(int holizontal, int vertical) :
	tilt(Vector2::Zero),
	tiltRadian(0.0f),
	tiltRatio(0.0f)
{
	if (holizontal)
	{
		// 水平方向の入力があれば入力割合を取得
		tilt.x = MyMath::Clamp(static_cast<float>(holizontal / kThumbInputMax), -1.0f, 1.0f);
	}
	if (vertical)
	{
		// 垂直方向の入力があれば入力割合を取得
		tilt.y = MyMath::Clamp(static_cast<float>(vertical / kThumbInputMax), -1.0f, 1.0f);
	}
	// 入力角度を求める
	tiltRadian = atan2(tilt.y, tilt.x);
	// 4方向の入力方向を取得
	int direction = static_cast<int>((tiltRadian - kDirectonFourCalculateValue) / (kDirectonFourCalculateValue * 2.0f));
	directionFour = static_cast<Input::DirectionFour>(direction);
	// 8方向の入力方向を取得
	direction = static_cast<int>((tiltRadian - kDirectonEightCalculateValue) / (kDirectonEightCalculateValue * 2.0f));
	directionEight = static_cast<Input::DirectionEight>(direction);
	// 入力があれば入力量を計算
	if (!tilt.x && !tilt.y)return;
	tiltRatio = tilt.GetLength() / static_cast<float>(kThumbInputMax);
}
