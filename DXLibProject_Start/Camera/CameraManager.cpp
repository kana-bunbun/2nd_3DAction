#include "CameraManager.h"
#include"../Utility/MyMath.h"
#include<cassert>
namespace {
	constexpr float kNearDistance = 5.0f;	// カメラの手前のクリップ距離
	constexpr float kFarDistance = 5000.0f;	// カメラの奥のクリップ距離
	constexpr float kFieldOfView = 60.0f;	// カメラの視野角
}

CameraManager::CameraManager():
	m_activeCamera(nullptr),
	m_currentView{},
	m_activeIndex(0)
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
	assert(!m_cameras.empty());
	if (m_cameras.empty())return;
	m_cameras[m_activeIndex]->Update();
	m_currentView=m_cameras[m_activeIndex]->GetView();
}

void CameraManager::Apply()
{
	SetCameraPositionAndTarget_UpVecY(
		m_currentView.position.ToVECTOR(),
		m_currentView.target.ToVECTOR()
	);

	// カメラの視野角を設定
	SetupCamera_Perspective(m_currentView.fov * MyMath::ToRadian);
}


void CameraManager::AddCamera(std::unique_ptr<ICamera> camera)
{
	m_cameras.push_back(std::move(camera));
}


void CameraManager::NextCamera()
{
	m_activeIndex = (m_cameras.size() + m_activeIndex++)% m_cameras.size();
}
