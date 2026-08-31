#pragma once
#include"Utility/Vector2.h"
#include"Utility/MyMath.h"
#include"Input/InputConst.h"
struct ThumbData {
	/// <summary>
	/// 入力量
	/// </summary>
	Vector2 tilt=Vector2::Zero;
	/// <summary>
	/// 入力角度(ラジアン)
	/// </summary>
	float tiltRadian=0.0f;
	/// <summary>
	/// 入力割合
	/// </summary>
	float tiltRatio=0.0f;
	/// <summary>
	/// 4方向のスティック入力
	/// </summary>
	DirectionFour directionFour=DirectionFour::Invalid;
	/// <summary>
	/// 8方向のスティック入力
	/// </summary>
	DirectionEight directionEight = DirectionEight::Invalid;
};
class InputThumb {
public:
	InputThumb();
	InputThumb(int holizontal = 0, int vertical = 0);
	const ThumbData GetThumbData()const { return m_thumbData; }
private:
	ThumbData m_thumbData;
};