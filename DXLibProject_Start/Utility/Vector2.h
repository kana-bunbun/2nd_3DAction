#pragma once

#include <DxLib.h>

/// <summary>
/// 2次元ベクトル構造体
/// UI実装の際に使用する想定
/// </summary>
struct Vector2
{
public:

	float x,y;

	//---------------------------------------------------------------------
	// プリセット
	//---------------------------------------------------------------------

	/// <summary>
	/// ゼロベクトル
	/// </summary>
	static const Vector2 zero;

	/// <summary>
	/// X軸の正方向の単位ベクトル
	/// Right,Leftは現状用意しない
	/// </summary>
	static const Vector2 XAxis;

	/// <summary>
	/// Y軸の正方向の単位ベクトル
	/// Up,Downは現状用意しない
	/// </summary>
	static const Vector2 YAxis;

	//---------------------------------------------------------------------
	// コンストラクタ
	//---------------------------------------------------------------------

	/// <summary>
	/// デフォルトコンストラクタ
	/// 定数宣言するために
	/// constexprをつける
	/// ヘッダーに処理を記載　している
	/// </summary>
	constexpr Vector2() : x(0.0f), y(0.0f) {}

	/// <summary>
	/// 引数ありのコンストラクタ
	/// 定数宣言するために
	/// constexprをつける
	/// ヘッダーに処理を記載　している
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	constexpr Vector2(float x, float y) : x(x), y(y) {}

	//---------------------------------------------------------------------
	// 演算
	//---------------------------------------------------------------------

	/// <summary>
	/// マイナスのベクトルを返す
	/// 各値に-をかける
	/// </summary>
	/// <returns></returns>
	Vector2 operator-() const;

	/// <summary>
	/// ベクトルの加算
	/// </summary>
	/// <param name="vec">足されるベクトル</param>
	/// <returns></returns>
	Vector2 operator+(const Vector2& vec) const;

	/// <summary>
	/// ベクトルの減算
	/// </summary>
	/// <param name="vec">引かれるベクトル</param>
	/// <returns></returns>
	Vector2 operator-(const Vector2& vec) const;

	/// <summary>
	/// ベクトルとスカラーの乗算
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2 operator*(float scale) const;

	/// <summary>
	/// ベクトルとスカラーの除算
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Vector2 operator/(float scale) const;

	/// <summary>
	/// ベクトルとベクトルの加算代入演算子
	/// 自分自身を変更するから参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator+= (const Vector2& vec);

	/// <summary>
	/// ベクトルとベクトルの減算代入演算子
	/// 自分自身を変更するから参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator-= (const Vector2& vec);

	/// <summary>
	/// ベクトルとスカラーの乗算代入演算子
	/// 自分自身を変更するから参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator*= (float scale);

	/// <summary>
	/// ベクトルとスカラーの除算代入演算子
	/// 自分自身を変更するから参照を返す
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	Vector2& operator/= (float scale);

	/// <summary>
	/// ベクトルの比較 等しいかどうか
	/// </summary>
	/// <param name="val"></param>
	/// <returns></returns>
	bool operator==(const Vector2& vec)const;

	/// <summary>
	/// ベクトルの比較 等しくないかどうか
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	bool operator!=(const Vector2& vec) const;

	//---------------------------------------------------------------------
	// ベクトル操作
	//---------------------------------------------------------------------

	/// <summary>
	/// ベクトルの長さを取得
	/// 平方根の処理が少し負荷があるので厳密な長さが必要じゃなければ非推奨
	/// </summary>
	/// <returns></returns>
	float GetLength() const;

	/// <summary>
	/// ベクトルの長さの二乗を取得
	/// </summary>
	/// <returns></returns>
	float GetSqLength() const;

	/// <summary>
	/// 正規化ベクトルを取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetNormalize() const;

	/// <summary>
	/// ベクトルの長さがほぼ0かどうか判定
	/// </summary>
	/// <returns>ほぼ0ならtrue</returns>
	bool IsLengthNearlyZero() const;

	/// <summary>
	/// 2つのベクトルの内積を求める
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	float Dot(const Vector2& vec) const;

	/// <summary>
	/// DxLibのVECTOR型に変換
	/// </summary>
	/// <returns></returns>
	VECTOR ToVECTOR() const;


};