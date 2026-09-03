#include "DebugCamera.h"
#include "Camera.h"
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/MyMath.h"
#include<DxLib.h>
#include<cmath>
#include"Input/InputData.h"

namespace {
    constexpr float kMoveSpeed = 5.0f;
    constexpr float kRotSpeed = 5.5f * MyMath::ToRadian;
    constexpr float kFieldOfView = 60.0f;

    constexpr float kPitchLimit = 89.0f * MyMath::ToRadian; // pich制限

    constexpr float kLowAngle = -30.0f * MyMath::ToRadian;				// カメラの最大仰角
    constexpr float kHighAngle = 80.0f * MyMath::ToRadian;				// カメラの最大俯角
}

DebugCamera::DebugCamera():
    m_transform{},
    m_view{},
    m_moveSpeed(kMoveSpeed),
    m_rotSpeed(kRotSpeed)
{

    m_view.target = Vector3::ZAxis;
    m_view.fov = kFieldOfView;

}

DebugCamera::~DebugCamera()
{

}

void DebugCamera::Update(float deltaTime, InputData inputData)
{
    // 移動量の計算 レバーを倒した割合にかける
    float moveAmount = inputData.GetInputRatio(Input::Action::Camera) * m_rotSpeed;
    if (!moveAmount)return;
    float inputRadian = inputData.GetRadian(Input::Action::Camera);
    float inputValue = inputData.GetInputRatio(Input::Action::Camera);
    float pitchRad = m_transform.rotation.x;
    float yawRad = m_transform.rotation.y;
    // 計算用のVector
    Vector3 m_moveVector = Vector3::zero;
    // 入力角度からX,Y方向の移動量を計算
    m_moveVector.x = -sinf(inputRadian);
    m_moveVector.y = -cosf(inputRadian);
    // 正規化
    m_moveVector = m_moveVector.Normalize();
  
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
    m_view.target = m_transform.position+Vector3(0,0,0);
    // 右方向のベクトルを取得
    Vector3 right;
    right.x = cosf(yawRad);
    right.y = 0.0f;
    right.z = -sinf(yawRad);
    right = right.Normalize();


    // 入力量を取得
    // 入力角度を取得
    float analogRadian = inputData.GetRadian(Input::Action::Camera);
    // カメラの角度で回転するように
    analogRadian += m_transform.rotation.y;


    Vector3 forward;
    forward.x = cosf(pitchRad) * sinf(yawRad);
    forward.y = cosf(pitchRad);
    forward.z = cosf(pitchRad) * cosf(yawRad);
    
    //float length = forward.GetLength();         // 長さデバッグ

    forward = forward.Normalize();
    //m_transform.Translate(move);

    printfDx("transform\n");
    printfDx("position\n");
    printfDx("x : %f", m_transform.position.x);
    printfDx("y : %f", m_transform.position.y);
    printfDx("z : %f\n", m_transform.position.z);
    printfDx("rotate\n");
    printfDx("x : %f", m_transform.rotation.x);
    printfDx("y : %f", m_transform.rotation.y);
    printfDx("z : %f\n", m_transform.rotation.z);
    UpdatePos();
}


Camera::CameraView DebugCamera::GetView() const
{
    return m_view;
}

void DebugCamera::UpdatePos()
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
    //rotate *= 100;


    Vector3 cameraPos = Vector3(0.0f, 0, 0.0f);

    cameraPos += m_view.target;
    cameraPos = (cameraPos + rotate);

    m_view.transform.position = cameraPos;
    //m_view.target = m_view.target;
    m_transform.position = cameraPos;

    m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
}
