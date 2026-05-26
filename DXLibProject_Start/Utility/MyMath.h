#pragma once

#include"../Utility/Vector3.h"
#include<math.h>

namespace MyMath {

	// ラジアン角に変更する定数
	constexpr float ToRadian = DX_PI_F / 180.0f;
	// デグリー角に変更する定数
	constexpr float ToDegree = 180.0f / DX_PI_F;

	/// <summary>
	/// 角度を-180度～180度までに収める関数
	/// </summary>
	/// <param name="angle">-180度～180度に収めたい値</param>
	/// <returns>-180度～180度に収めた値</returns>
	constexpr float NormalizeAngle(float angle) {
		while (angle > 180.0f)angle -= 360.0f;
		while (angle < -180.0f)angle += 360.0f;

		return angle;

	}

	/// <summary>
	/// 角度を-180度～180度までに収める関数
	/// </summary>
	/// <param name="angle">-180度～180度に収めたい値</param>
	/// <returns>-180度～180度に収めた値</returns>
	constexpr float NormalizeRadian(float radian) {
		while (radian > DX_PI_F)radian -= DX_PI_F*2;
		while (radian < -DX_PI_F)radian += DX_PI_F*2;
		
		return radian;

	}

	/// <summary>
	/// 地域の間に収める
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value">調べたい数</param>
	/// <param name="min">調べたい数の最小の値</param>
	/// <param name="max">調べたい数の最大の値</param>
	/// <returns></returns>
	template <typename T>
	constexpr T Clamp(T value, T min, T max) {
		if (value < min)return min;
		if (value > max)return max;

		return value;

	}
	/// <summary>
	/// 最大値からの割合を返す
	/// </summary>
	/// <param name="value">調べたい値</param>
	/// <param name="Max">最大値</param>
	/// <returns></returns>
	constexpr float Rate(float value, float max) {
		return value / max;
	}

	/// <summary>
	/// 1か-1に変換して返す関数
	/// </summary>
	/// <param name="value">変換したい値</param>
	/// <returns>値が正なら1、負なら-1を返す</returns>
	constexpr int Sign(float value) {
		if (value >= 0)return 1;
		return -1;
	}

	/// <summary>
	/// 二点間の座標の差から距離を計算する関数
	/// </summary>
	/// <param name="pos1">1つ目の座標</param>
	/// <param name="pos2">2つ目の座標</param>
	/// <returns>2点間の距離</returns>
	constexpr float Distance(Vector3 pos1, Vector3 pos2) {


		// X座標、Y座標、Z座標の差から距離を計算した値を返す
		return
			(pos1.x - pos2.x) * (pos1.x - pos2.x) +
			(pos1.y - pos2.y) * (pos1.y - pos2.y) +
			(pos1.z - pos2.z) * (pos1.z - pos2.z);

	}
	constexpr float DistanceHolizontal(Vector3 pos1, Vector3 pos2) {


		// X座標、Z座標の差から距離を計算した値を返す
		return
			(pos1.x - pos2.x) * (pos1.x - pos2.x) +
			(pos1.z - pos2.z) * (pos1.z - pos2.z);

	}

	template <typename T>
	constexpr const T& Min(const T& a, const T& b) {
		if(a>b)return b;
		return a;
	}
	template <typename T>
	constexpr const T& Max(const T& a, const T& b) {
		if (a > b)return a;
		return b;
	}
	constexpr const float Abs(float value) {
		float res = value;
		if (res < 0)res *= -1;
		return res;
	}
}

