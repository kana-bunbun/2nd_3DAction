#include "DebugCamera.h"
#include "Camera.h"
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include<DxLib.h>
#include<cmath>
#include"../Utility/MyMath.h"
#include"../Utility/Input.h"

namespace {
    constexpr float kMoveSpeed = 5.0f;
    constexpr float kRotSpeed = 1.5f * MyMath::ToRadian;
    constexpr float kFieldOfView = 60.0f;

    constexpr float kPitchLimit = 89.0f * MyMath::ToRadian; // pich制限
}

DebugCamera::DebugCamera(const Transform* target):
    m_transform{},
    m_view{},
    m_moveSpeed(kMoveSpeed),
    m_rotSpeed(kRotSpeed)
{

}

DebugCamera::~DebugCamera()
{

}

void DebugCamera::Update()
{

}

Camera::CameraView DebugCamera::GetView() const
{
    return Camera::CameraView();
}

Vector3 DebugCamera::GetForward() const
{
    return Vector3();
}

float DebugCamera::GetYawRad() const
{
    return 0.0f;
}
