#pragma once
#include "Camera.h"
#include "../Utility/Vector3.h"
#include "../World/Component/Transform.h"

/// <summary>
/// プレイヤーを追従するカメラ
/// </summary>
class FollowCamera : public ICamera
{
public:
	FollowCamera(const Transform* target);
	~FollowCamera();

	/// =========================================
	///		ICamera クラスのメンバ変数
	/// =========================================

	void Update()override;
	Camera::CameraView GetView()const override;
	Vector3 GetForward()const override;
	float GetYawRad()const override;

	/// =========================================
	///		FollowCamera クラスのメンバ変数
	/// =========================================
	
	/// <summary>
	/// 被写体との距離を更新
	/// </summary>
	void UpdateDistance();
	/// <summary>
	/// カメラの角度を更新
	/// </summary>
	void UpdateAngle();
	/// <summary>
	/// カメラの座標を更新
	/// </summary>
	void UpdatePosition();

private:

	/// <summary>
	/// 追従対象
	/// 読み取り専用
	/// </summary>
	const Transform* m_target;
	/// <summary>
	/// カメラデータ
	/// </summary>
	Camera::CameraView m_view;
	/// <summary>
	/// カメラの座標・回転・拡縮
	/// </summary>
	Transform m_transsform;
	/// <summary>
	/// targetとの距離
	/// </summary>
	float m_distance;

};

