#pragma once
#include"Utility/Vector2.h"
#include"Utility/MyMath.h"
#include"Input/InputConst.h"
#include"Input/VectorState.h"
struct ThumbData {
	/// <summary>
	///ベクトルの入力情報
	/// </summary>
	VectorState vectorState;
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
	const Vector2 GetVector(){ return m_thumbData.vectorState.GetVector(); }
	const DirectionFour GetDirectionFour() { return m_thumbData.directionFour; }
	const DirectionEight GetDirectionEight() { return m_thumbData.directionEight; }
	const float GetRadian() { return m_thumbData.vectorState.GetRadian(); }
	const float GetRatio() { return m_thumbData.vectorState.GetRatio(); }
private:
	ThumbData m_thumbData;
};