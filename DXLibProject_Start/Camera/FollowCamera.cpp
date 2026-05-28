#include "FollowCamera.h"
#include "Camera.h"

#include"../Utility//Vector3.h"
#include"../World/Component/Transform.h"

#include<cassert>
#include<math.h>

#include "../Utility/Input.h"
#include "../Utility/MyMath.h"

namespace {
    constexpr float kFieldOfView = 60.0f;       	// カメラの視野角 FOV = field of view

    constexpr float kDistanceToTarget = 600.0f; 	// カメラの被写体までの初期距離
    constexpr float kMinDistance = 150;         	// 被写体との最短距離
    constexpr float kMaxDistance = 150;         	// 被写体との最長距離
    constexpr float kAngleSpeed = 2.0f;         	// カメラの角速度

    constexpr float kInitCameraHeight = 150.0f;		// カメラの初期の高さ
    constexpr float kLowAngle = -30.0f;				// カメラの最大仰角
    constexpr float kHighAngle = 80.0f;				// カメラの最大俯角
}

FollowCamera::FollowCamera(const Transform* target):
    m_target(target),
    m_view{},
    m_distance(kDistanceToTarget)
{

}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
{
    UpdateDistance();
    UpdateAngle();
    UpdatePosition();
}

Camera::CameraView FollowCamera::GetView() const
{
    return m_view;
}

Vector3 FollowCamera::GetForward() const
{
    Vector3 dir = m_view.target - m_view.position;
    return dir.Normalize();
}

float FollowCamera::GetYawRad() const
{
    return m_transsform.rotation.y;
}

void FollowCamera::UpdateDistance()
{
    // カメラの最短距離、最長距離を求める
    float minDistance = kDistanceToTarget - kMinDistance;
    float maxDistance = kDistanceToTarget - kMaxDistance;

    minDistance = MyMath::Clamp(minDistance, 0.0f, kDistanceToTarget);
    maxDistance = MyMath::Clamp(maxDistance, kDistanceToTarget, maxDistance);
    // 距離を指定範囲内に収める
    m_distance = MyMath::Clamp(m_distance, minDistance, maxDistance);
}

void FollowCamera::UpdateAngle()
{

}

void FollowCamera::UpdatePosition()
{

}
