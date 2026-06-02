#pragma once
#include"../Utility/Game.h"
#include"../Utility/Input.h"
#include"../World/Component/Transform.h"
// 前方宣言
class Player;

/// <summary>
/// カメラのクラス
/// </summary>
class CameraOld
{

public:

	CameraOld();
	~CameraOld();

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init( Player* pPlayer );

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// カメラの水平アングルを取得する
	/// </summary>
	/// <returns>カメラの水平アングル</returns>
	float GetHRadian()const { return m_transform.rotation.y; }

	/// <summary>
	/// コントローラーを割り当てる
	/// </summary>
	/// <param name="padNum">コントローラーの番号</param>
	/// <returns></returns>
	void SetPad(const Pad::Player padNum) { m_pad = padNum; }
	/// <summary>
	/// カメラの水平方向(ヨー)のラジアン角を取得する関数
	/// </summary>
	/// <returns>カメラの水平方向(ヨー)のラジアン角</returns>
	float GetYawRadian()const { return m_transform.rotation.y; }
	/// <summary>
	/// カメラが追従するターゲットを設定
	/// </summary>
	/// <param name="transform">追従するターゲットのTransform</param>
	/// <returns></returns>
	const void SetTarget(const Transform& transform) { m_target = transform; }
	const void SetInput(bool input) { m_input = input; }
	float CheckAlpha(const Vector3& vec);

	void SetCameraAngle(const Vector3& angle) { m_transform.rotation = angle; }
	const Transform GetTransform()const { return m_transform; }
private:

	/// <summary>
	/// 被写体との距離を更新
	/// </summary>
	void UpdateDistance();

	/// <summary>
	/// 入力に基づいたカメラの角度を更新
	/// </summary>
	void UpdateAngleInput();
	/// <summary>
	/// 補間での角度の更新処理
	/// </summary>
	void UpdateAngleLerp();
	/// <summary>
	///  カメラの角度から位置を計算して更新
	/// </summary>
	void UpdateCameraPos();
private:

	///// <summary>
	///// カメラの水平方向の角度
	///// </summary>
	//float m_hAngle;

	///// <summary>
	///// カメラの水平方向のラジアン角
	///// </summary>
	//float m_hRadian;

	///// <summary>
	///// カメラの垂直方向の角度
	///// </summary>
	//float m_vAngle;

	///// <summary>
	///// カメラの垂直方向のラジアン角
	///// </summary>
	//float m_vRadian;

	/// <summary>
	/// 自身の座標・回転・拡縮
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// 現在のカメラの被写体までの距離
	/// </summary>
	float m_currentDistance;
	/// <summary>
	/// 補間する際の目標となる距離
	/// </summary>
	float m_desireDistance;
	/// <summary>
	/// 距離の補間の割合
	/// </summary>
	float m_lerpDistance;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;

	Transform m_target;
	/// <summary>
	/// 自身を操作するコントローラー
	/// </summary>
	Pad::Player m_pad;
	/// <summary>
	/// 入力に基づいた角度の更新処理をするかどうかのフラグ
	/// </summary>
	bool m_input;
};

