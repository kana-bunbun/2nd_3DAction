#include "FollowCamera.h"
#include "Camera.h"

#include"../Utility//Vector3.h"
#include"../World/Component/Transform.h"

#include<cassert>
#include<math.h>

#include "../Utility/Input.h"
#include "../Utility/MyMath.h"
#include "../Utility/Time.h"


namespace {
    constexpr float kFieldOfView = 60.0f;       	// カメラの視野角 FOV = field of view

    constexpr float kDistanceToTarget = 600.0f; 	// カメラの被写体までの初期距離
    constexpr float kMinDistance = 150;         	// 被写体との最短距離
    constexpr float kMaxDistance = 150;         	// 被写体との最長距離
    constexpr float kAngleSpeed = 2.0f;         	// カメラの角速度

    constexpr float kInitCameraHeight = 150.0f;		// カメラの初期の高さ
    constexpr float kLowAngle = -30.0f * MyMath::ToRadian;				// カメラの最大仰角
    constexpr float kHighAngle = 80.0f * MyMath::ToRadian;				// カメラの最大俯角
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
    printfDx("/////transform/////\n");
    printfDx("rotation  X : %f\n",m_transform.rotation.x * MyMath::ToDegree);
    printfDx("rotation  Y : %f\n", m_transform.rotation.y * MyMath::ToDegree);
    printfDx("rotation  Z : %f\n", m_transform.rotation.z * MyMath::ToDegree);
}

Camera::CameraView FollowCamera::GetView() const
{
    return m_view;
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

    float deltaTime=Time::GetInstance().GetDeltaTime();

    float inputRadian = Input::AnalogAngle(Input::Joystick::Right, Pad::Player::P1)*MyMath::ToRadian;
    float inputValue = Input::PadAnalogAmount(Input::Joystick::Right, Pad::Player::P1);
    float pitchRad = m_transform.rotation.x;
    float yawRad = m_transform.rotation.y;
    // 計算用のVECTOR
    Vector3 m_moveVector = Vector3::zero;
    // 入力角度からX,Y方向の移動量を計算
    m_moveVector.x = -sinf(inputRadian);
    m_moveVector.y = -cosf(inputRadian);
    // 正規化
    m_moveVector = m_moveVector.Normalize();
    // 移動量の計算 レバーを倒した割合にかける
    float moveAmount = Input::PadAnalogAmount(Input::Joystick::Right, Pad::Player::P1) * kAngleSpeed;
    // 移動速度をかける
    m_moveVector = (m_moveVector * moveAmount);
    pitchRad += m_moveVector.y * deltaTime;
    pitchRad = MyMath::Clamp(pitchRad, kLowAngle, kHighAngle);
    m_transform.rotation.x = pitchRad;

    yawRad = MyMath::NormalizeRadian(yawRad);




    yawRad -= m_moveVector.x * deltaTime;
    // 水平方向の角度を範囲内に収める
    yawRad = MyMath::NormalizeAngle(yawRad);
    m_transform.rotation.y = yawRad /** MyMath::ToRadian*/;

}

void FollowCamera::UpdatePosition()
{

    //assert(m_target);
    //if (m_target)return;

    // 水平方向の成分
    float sinHol = sinf(m_transform.rotation.y);
    float cosHol = cosf(m_transform.rotation.y);
    // 垂直方向の成分
    float sinVer = sinf(m_transform.rotation.x);
    float cosVer = cosf(m_transform.rotation.x);
    // ベクトルの計算
    Vector3 rotate;
    rotate.x = cosVer * sinHol;
    rotate.y = sinVer;
    rotate.z = cosVer * cosHol;
    rotate *= m_distance;
    
    
    Vector3 cameraPos = Vector3(0.0f, kInitCameraHeight, 0.0f);

    cameraPos += m_target->position;
    cameraPos = (cameraPos + rotate);

    m_view.position = cameraPos;
    m_view.target = m_target->position;
    m_transform.position = cameraPos;

    m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
}
