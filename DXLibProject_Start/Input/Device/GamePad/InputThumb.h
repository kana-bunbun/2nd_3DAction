#pragma once
#include"Utility/Vector2.h"
#include"Input/InputConst.h"

class InputThumb {
public:
	InputThumb();
	InputThumb(int holizontal = 0, int vertical = 0);
	/// <summary>
	/// 傾けた量
	/// </summary>
	Vector2 tilt;
	/// <summary>
	/// 入力角度
	/// </summary>
	float tiltRadian;
	/// <summary>
	/// 入力割合
	/// </summary>
	float tiltRatio;
	/// <summary>
	/// 4方向の入力方向
	/// </summary>
	Input::DirectionFour directionFour;
	/// <summary>
	/// 8方向の入力方向
	/// </summary>
	Input::DirectionEight directionEight;
};