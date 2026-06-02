#include "CameraManager.h"

namespace {
	constexpr float kNearDistance = 5.0f;	// カメラの手前のクリップ距離
	constexpr float kFarDistance = 5000.0f;	// カメラの奥のクリップ距離
	constexpr float kFieldOfView = 60.0f;	// カメラの視野角
}

CameraManager::CameraManager():
	m_activeCamera(nullptr),
	m_currentView{}
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::Init()
{
	SetCameraNearFar(kNearDistance, kFarDistance);
}

void CameraManager::Update()
{

}

void CameraManager::Apply()
{
}

void CameraManager::SetActiveCamera(std::unique_ptr<ICamera> camera)
{

}

Vector3 CameraManager::GetForward() const
{
	return Vector3();
}

float CameraManager::GetYawRad() const
{
	return 0.0f;
}
