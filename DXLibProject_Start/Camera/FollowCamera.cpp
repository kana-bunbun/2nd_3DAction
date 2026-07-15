#include "FollowCamera.h"
#include "Camera.h"

#include"../Utility//Vector3.h"
#include"../World/Component/Transform.h"

#include<cassert>
#include<math.h>

#include "../Utility/Input.h"
#include "../Utility/MyMath.h"
#include "../Utility/MyRandom.h"
#include "../Data/CameraParam.h"


FollowCamera::FollowCamera(const Transform* target):
    m_target(target),
    m_view{},
    m_distance(),
    m_param()
{
    m_param = FollowCameraParam();
    m_distance = m_param.initDistance;
    m_transform.Reset();
    m_transform.rotation.x = (m_param.maxPitchDegAngle+m_param.minPitchDegAngle)*0.5f * MyMath::ToRadian;
    m_view.fov = m_param.fieldOfView;
}

FollowCamera::FollowCamera(const Transform* target, const FollowCameraParam& param) :
    m_target(target),
    m_view{},
    m_distance(),
    m_param()
{
    m_distance = m_param.initDistance;
    m_transform.Reset();
    m_transform.rotation.x = (m_param.maxPitchDegAngle+m_param.minPitchDegAngle)*0.5f * MyMath::ToRadian;
    m_view.fov = m_param.fieldOfView;
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update(float deltaTime)
{
    UpdateDistance(deltaTime);
    UpdateAngle(deltaTime);
    UpdatePosition(deltaTime);
    //printfDx("/////transform/////\n");
    //printfDx("rotation  X : %f\n",m_transform.rotation.x * MyMath::ToDegree);
    //printfDx("rotation  Y : %f\n", m_transform.rotation.y * MyMath::ToDegree);
    //printfDx("rotation  Z : %f\n", m_transform.rotation.z * MyMath::ToDegree);
}

Camera::CameraView FollowCamera::GetView() const
{
    return m_view;
}

void FollowCamera::UpdateDistance(float deltaTime)
{
    // カメラの最短距離、最長距離を求める
    float minDistance = m_param.initDistance - m_param.minDistance;
    float maxDistance = m_param.initDistance - m_param.maxDistance;

    minDistance = MyMath::Clamp(minDistance, 0.0f, m_param.initDistance);
    maxDistance = MyMath::Clamp(maxDistance, m_param.initDistance, maxDistance);
    // 距離を指定範囲内に収める
    m_distance = MyMath::Clamp(m_distance, minDistance, maxDistance);
}

void FollowCamera::UpdateAngle(float deltaTime)
{

    float inputRadian = Input::AnalogAngle(Input::Joystick::Right, Input::Pad::P1)*MyMath::ToRadian;
    float inputValue = Input::PadAnalogAmount(Input::Joystick::Right, Input::Pad::P1);
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
    float moveAmount = Input::PadAnalogAmount(Input::Joystick::Right, Input::Pad::P1) * m_param.rotateSpeedDeg;
    // 移動速度をかける
    m_moveVector = (m_moveVector * moveAmount);
    pitchRad += m_moveVector.y * deltaTime;
    pitchRad = MyMath::Clamp(pitchRad, m_param.minPitchDegAngle*MyMath::ToRadian, m_param.maxPitchDegAngle * MyMath::ToRadian);
    m_transform.rotation.x = pitchRad;

    yawRad = MyMath::NormalizeRadian(yawRad);




    yawRad -= m_moveVector.x * deltaTime;
    // 水平方向の角度を範囲内に収める
    yawRad = MyMath::NormalizeAngle(yawRad);
    m_transform.rotation.y = yawRad /** MyMath::ToRadian*/;

}

void FollowCamera::UpdatePosition(float deltaTime)
{

    //assert(m_target);
    //if (m_target)return;
    float randRange = DX_PI_F * 0.0f;
    float rotateX = m_transform.rotation.x + (MyRandom::Float(-randRange, randRange));
    float rotateY = m_transform.rotation.y + (MyRandom::Float(-randRange, randRange));

    // 水平方向の成分
    float sinHol = sinf(rotateY);
    float cosHol = cosf(rotateY);
    // 垂直方向の成分
    float sinVer = sinf(rotateX);
    float cosVer = cosf(rotateX);
    // ベクトルの計算
    Vector3 rotate;
    rotate.x = cosVer * sinHol;
    rotate.y = sinVer;
    rotate.z = cosVer * cosHol;
    rotate *= m_distance;
    
    
    Vector3 cameraPos = Vector3(0.0f, 0.0f, 0.0f);

    cameraPos += m_target->position;
    cameraPos = (cameraPos + rotate);

    m_view.position = cameraPos;
    m_view.target = m_target->position;
    m_view.target += m_param.offsetPos;
    m_transform.position = cameraPos;



    m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
    if (m_transform.position.y < 0)
    {
        m_transform.position.y = 0;
    }
}
