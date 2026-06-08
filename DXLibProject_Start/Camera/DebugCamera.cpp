#include "DebugCamera.h"
#include "Camera.h"
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../Utility/MyMath.h"
#include"../Utility/Time.h"
#include<DxLib.h>
#include<cmath>
#include"../Utility/Input.h"

namespace {
    constexpr float kMoveSpeed = 5.0f;
    constexpr float kRotSpeed = 1.5f * MyMath::ToRadian;
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

}

DebugCamera::~DebugCamera()
{

}

void DebugCamera::Update()
{
    float deltaTime = Time::GetInstance().GetDeltaTime();

    float inputRadian = Input::AnalogAngle(Input::Joystick::Right, Pad::Player::P1) * MyMath::ToRadian;
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
    float moveAmount = Input::PadAnalogAmount(Input::Joystick::Right, Pad::Player::P1) * m_rotSpeed;
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
    m_view.target = m_transform.position+Vector3(1,0,0);
    // 右方向のベクトルを取得
    Vector3 right;
    right.x = cosf(yawRad);
    right.y = 0.0f;
    right.z = -sinf(yawRad);
    right = right.Normalize();

    Vector3 move=Vector3::zero;

    // 入力量を取得
    float analogAmount = Input::PadAnalogAmount(Input::Joystick::Left, Pad::Player::P1);
    // 入力角度を取得
    float analogAngle = Input::AnalogAngle(Input::Joystick::Left, Pad::Player::P1);
    // 角度をラジアン角に変更
    analogAngle *= MyMath::ToRadian;
    // カメラの角度で回転するように
    analogAngle += m_transform.rotation.y;


    // 移動をする
    //m_move.Update();

    //float deltaTime = Time::GetInstance().GetDeltaTime();

    Vector3 moveVec = Vector3::zero;
    moveVec.x = -sinf(analogAngle);
    moveVec.z = -cosf(analogAngle);
    moveVec *= 10*analogAmount;
    move= moveVec * deltaTime;

    m_view.GetForward();

    m_transform.Translate(move);

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

    m_view.position = cameraPos;
    //m_view.target = m_view.target;
    m_transform.position = cameraPos;

    m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
}
