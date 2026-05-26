#pragma once
#include<DxLib.h>
/// <summary>
/// 3次元ベクトル構造体
/// 基本的には値として使うことが多いので構造体で作成する
/// →publicで作っていくが、気になればprivateを使い分ける
/// 処理が膨大になってきたらクラスに変更すればよい
/// </summary>
class Vector3 {
public:

	/// <summary>
	/// 各軸の座標
	/// </summary>
	float x, y, z;
public:
	//==================================================
	//		プリセット
	//==================================================

	/// <summary>
	/// ゼロベクトル
	/// </summary>
	static const Vector3 zero;

	/// <summary>
	/// X軸の正方向の単位ベクトル
	/// </summary>
	static const Vector3 XAxis;

	/// <summary>
	/// Y軸の正方向の単位ベクトル
	/// </summary>
	static const Vector3 YAxis;

	/// <summary>
	/// Z軸の正方向の単位ベクトル
	/// </summary>
	static const Vector3 ZAxis;

public:
	/// <summary>
	/// デフォルトコンストラクタ
	/// 定数宣言の際にも使用できるよう consterxpr をつけて宣言
	/// </summary>
	constexpr Vector3() :x(0.0f), y(0.0f), z(0.0f){}
	/// <summary>
	/// 引数ありのコンストラクタ
	/// 定数宣言の際にも使用できるよう consterxpr をつけて宣言
	/// </summary>
	/// <param name="x">x方向の値</param>
	/// <param name="y">y方向の値</param>
	/// <param name="z">z方向の値</param>
	constexpr Vector3(float x,float y,float z) :x(x), y(y), z(z){}


	// Vector3の演算
	Vector3 operator=(float value)const;					// マイナスのベクトルを返す
	Vector3 operator-()const;					// マイナスのベクトルを返す
	Vector3 operator+(const Vector3& vec)const;		// ベクトルの加算
	Vector3& operator+=(const Vector3& vec);	// ベクトルの加算代入演算子
	Vector3 operator-(const Vector3& vec)const;		// ベクトルの減算
	Vector3& operator-=(const Vector3& vec);	// ベクトルの減算代入演算子
	Vector3 operator* (float value)const;		// ベクトルとスカラーの乗算
	Vector3& operator*=(float value);			// ベクトルとスカラーの乗算代入演算子
	Vector3 operator/(float value)const;		// ベクトルとスカラーの除算
	Vector3& operator/=(float value);			// ベクトルとスカラーの除算代入演算子
	bool operator ==(const Vector3& vec)const;		// 2つのベクトルが等しいかどうか
	bool operator !=(const Vector3& vec)const;		// 2つのベクトルが異なるかどうか
	float GetLength()const;						// ベクトルの大きさを取得する関数
	float GetSqLength()const;						// ベクトルの大きさを取得する関数
	Vector3 Normalize()const;					// ベクトルを正規化する
	/// <summary>
	/// DxLibのVECTOR型に変換する関数
	/// </summary>
	/// <returns></returns>
	VECTOR ToVECTOR()const;

};