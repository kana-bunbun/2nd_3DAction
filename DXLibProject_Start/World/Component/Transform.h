#pragma once
#include"../../Utility/Vector3.h"
#include"../../Utility/MyMath.h"

/// <summary>
/// 座標・回転・拡縮を管理する構造体
/// </summary>
struct Transform
{
public:
	/// <summary>
	/// 座標(ワールド座標)
	/// </summary>
	Vector3 position{ 0.0f,0.0f,0.0f };

	/// <summary>
	/// 回転(ラジアン角)
	/// 三角関数との親和性を考慮し、ラジアン角で扱う
	/// </summary>
	Vector3 rotation{ 0.0f,0.0f,0.0f };

	/// <summary>
	/// 拡大率(1.0で等倍)
	/// </summary>
	Vector3 scale{ 1.0f,1.0f,1.0f };
public:
	/// <summary>
	/// 座標の移動
	/// </summary>
	/// <param name="vec">移動成分のベクトル</param>
	void Translate(const Vector3& vec) { position += vec; }
	/// <summary>
	/// 回転(ラジアン角)
	/// </summary>
	/// <param name="vec">回転成分のベクトル</param>
	void RotateRad(const Vector3& vec) { rotation += vec; }
	/// <summary>
	/// 回転(デグリー角で指定)
	/// </summary>
	/// <param name="vec">回転成分のベクトル</param>
	void RotateDeg(const Vector3& vecDeg) { rotation += vecDeg * MyMath::ToDegree; }
	/// <summary>
	/// 角度を指定(デグリー角で指定)
	/// </summary>
	/// <param name="vecDeg">回転成分のベクトル</param>
	void SetRotateDeg(const Vector3& vecDeg) { rotation = vecDeg * MyMath::ToDegree; }
	/// <summary>
	/// 回転の値をデグリー角で取得する関数
	/// </summary>
	/// <returns>デグリー角の回転成分</returns>
	Vector3 VetRotateDeg()const { return rotation * MyMath::ToRadian; }
	/// <summary>
	/// 各値の初期化
	/// </summary>
	void Reset() {
		position = Vector3::zero;
		rotation= Vector3::zero;
		scale = { 1.0f,1.0f,1.0f };
	}
};

