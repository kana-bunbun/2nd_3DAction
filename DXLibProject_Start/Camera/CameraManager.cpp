#include "CameraManager.h"
#include"../Utility/MyMath.h"
#include<cassert>
namespace {
	constexpr float kNearDistance = 5.0f;	// カメラの手前のクリップ距離
	constexpr float kFarDistance = 5000.0f;	// カメラの奥のクリップ距離
	constexpr float kFieldOfView = 60.0f;	// カメラの視野角
}

CameraManager::CameraManager() :
	m_activeCamera(nullptr),
	m_currentView{},
	//m_activeIndex(0)
	m_cameraType(Camera::CameraType::Follow)
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
	//if (m_cameras.empty())return;
	//m_cameras[m_activeIndex]->Update();
	//m_currentView=m_cameras[m_activeIndex]->GetView();
	size_t index = static_cast<size_t>(m_cameraType);
	if (!m_cameras[index])return;
	m_cameras[index]->Update();
	m_currentView = m_cameras[index]->GetView();
}

void CameraManager::Apply()
{
	size_t index = static_cast<size_t>(m_cameraType);
	if (!m_cameras[index])return;

	SetCameraPositionAndTarget_UpVecY(
		m_currentView.position.ToVECTOR(),
		m_currentView.target.ToVECTOR()
	);

	// カメラの視野角を設定
	SetupCamera_Perspective(m_currentView.fov * MyMath::ToRadian);
}


void CameraManager::AddCamera(Camera::CameraType type, std::unique_ptr<ICamera> camera)
{
	if (static_cast<int>(type) >= m_cameras.size()) {
	while (static_cast<int>(type) >= m_cameras.size())
	{
		m_cameras.push_back(std::move(camera));
		
	}
	return;
	}

	m_cameras[static_cast<size_t>(type)] = std::move(camera);
	//m_cameras.push_back(std::move(camera));
}


void CameraManager::SetAcctiveCamera(Camera::CameraType type)
{
	m_cameraType = type;
}

void CameraManager::NextCamera()
{

	//m_activeIndex = (m_cameras.size() + m_activeIndex++)% m_cameras.size();
	//if (m_activeIndex<0 || m_activeIndex > m_cameras.size() - 1)m_activeIndex = 0;

	size_t index = static_cast<size_t>(m_cameraType);
	index++;
	index = MyMath::Clamp(index, static_cast<size_t>(0), static_cast<size_t>(Camera::CameraType::Max));
	if (!m_cameras[index])return;

}
