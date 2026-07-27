#pragma once
/// <summary>
/// 効果のパラメータ
/// </summary>
class ActionEffectParam {
public:
	int ID = -1;
	/// <summary>
	/// 効果発動時間(秒)
	/// </summary>
	float maxSecond = 0;
	/// <summary>
	/// 効果発動時間のインターバル
	/// </summary>
	float interval = 0;
	/// <summary>
	/// 効果の値
	/// </summary>
	int power;
};