#pragma once
#include "Camera.h"

#include "../Utility/Vector3.h"
#include "../World/Component/Transform.h"

#include "../Data/CameraParam.h"
/// <summary>
/// プレイヤーを追従するカメラ
/// </summary>
class FollowCamera : public ICamera
{
public:
	FollowCamera(const Transform* target);
	FollowCamera(const Transform* target,const FollowCameraParam& param);
	~FollowCamera();

	/// =========================================
	///		ICamera クラスのメンバ変数
	/// =========================================

	void Update(float deltaTime)override;
	Camera::CameraView GetView()const override;


	/// =========================================
	///		FollowCamera クラスのメンバ変数
	/// =========================================
	
	/// <summary>
	/// 被写体との距離を更新
	/// </summary>
	void UpdateDistance(float deltaTime);
	/// <summary>
	/// カメラの角度を更新
	/// </summary>
	void UpdateAngle(float deltaTime);
	/// <summary>
	/// カメラの座標を更新
	/// </summary>
	void UpdatePosition(float deltaTime);



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
	Transform m_transform;
	/// <summary>
	/// targetとの距離
	/// </summary>
	float m_distance;
	/// <summary>
	/// FollowCameraのパラメータ群
	/// </summary>
	FollowCameraParam m_param;

};

