#pragma once

class Gauge
{
public:
	Gauge();
	Gauge(float max,float value,float min);
	~Gauge();
	void Init();
	void End();

	/// <summary>
	/// 値を増加させる関数
	/// </summary>
	/// <param name="value">増加量</param>
	void Increase(float value);
	/// <summary>
	/// 値を減少させる関数
	/// </summary>
	/// <param name="value">減少量</param>
	void Decrease(float value);
	/// <summary>
	/// 最大値～最小値までの範囲にする
	/// </summary>
	void Clamp();
public:
	/// <summary>
	/// 現在の値を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetValue();
	/// <summary>
	/// ゲージの最大値を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetMax();
	/// <summary>
	/// ゲージの最小値を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetMin();
	/// <summary>
	/// ゲージの割合を取得する関数
	/// </summary>
	/// <returns></returns>
	float GetRate();
	/// <summary>
	/// 値を設定する関数
	/// </summary>
	void SetValue(float value);
	/// <summary>
	/// 最大値を設定する関数
	/// </summary>
	void SetMax(float max);
	/// <summary>
	/// 最小値を設定する関数
	/// </summary>
	void SetMin(float min);
private:
	/// <summary>
	/// <summary>
	/// ゲージの量
	/// </summary>
	float m_value;
	/// 最大値
	/// </summary>
	float m_max;
	/// <summary>
	/// 最小値
	/// </summary>
	float m_min;
};

