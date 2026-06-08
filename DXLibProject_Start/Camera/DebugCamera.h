#pragma once
#include "Camera.h"
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
class DebugCamera :public ICamera
{
public:
	DebugCamera();
	~DebugCamera();

	/// =========================================
	///		ICamera クラスのメンバ変数
	/// =========================================

	void Update()override;
	Camera::CameraView GetView()const override;


	void UpdatePos();

private:
	Transform m_transform;
	Camera::CameraView m_view;
	float m_moveSpeed;
	float m_rotSpeed;

};

