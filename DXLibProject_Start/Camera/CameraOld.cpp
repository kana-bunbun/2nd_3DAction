#include "CameraOld.h"

#include "../Utility/Vector3.h"
#include <math.h>
#include <cassert>
#include"../World/Character/Player/Player.h"
#include "../Utility/Input.h"
#include "../Utility/MyMath.h"
#include "../Utility/Game.h"

namespace {

	constexpr float kNearDistance = 5.0f;	// カメラの手前クリップ距離
	constexpr float kFarDistance = 5.0f;	// カメラの奥クリップ距離
	constexpr float kFieldOfView = 60.0f;	// カメラの視野角 FOV = FieldOfView

	constexpr float kDistanceToTarget = 600.0f;	// カメラの被写体までの初期距離
	constexpr float kMinDistance = 150;	// 被写体との最短距離
	constexpr float kMaxDistance = 150;	// 被写体との最長距離

	constexpr float kInitCameraHeight = 150.0f;		// カメラの初期の高さ

	constexpr float kPosLerp = 0.02f;

	constexpr float kLowAngle = -40.0f;				// カメラの最大仰角
	constexpr float kHighAngle = 80.0f;				// カメラの最大俯角

	constexpr float kAngleSpeed = 2.0f;	// カメラの角速度
	constexpr float kDefoultLerp = 0.2f;	// カメラ距離の基本の補間割合

	constexpr float kAlpha = 200;
	constexpr float kDistance = kAlpha * kAlpha;
}


CameraOld::CameraOld() :
	m_transform(),
	m_currentDistance(kDistanceToTarget),
	m_desireDistance(kDistanceToTarget),
	m_lerpDistance(kDefoultLerp),
	m_pPlayer(nullptr),
	m_target(),
	m_pad(Pad::Player::P1),
	m_input(true)
{
}

CameraOld::~CameraOld(){
	m_pPlayer = nullptr;
	delete m_pPlayer;

}

void CameraOld::Init( Player* pPlayer )
{

	// カメラのクリッピング距離の設定
	SetCameraNearFar(kNearDistance, kFarDistance);
	// カメラの視野角を設定
	SetupCamera_Perspective(kFieldOfView * DX_PI_F / 180.0f);
	// カメラの視点、注視点の初期設定
	SetCameraPositionAndTarget_UpVecY(
		Vector3(0.0f, 1700.0f, -400.0f).ToVECTOR(),
		Vector3(0.0f, 0.0f, -100.0f).ToVECTOR()
	);
	
	m_pPlayer = pPlayer;
}

void CameraOld::End(){}

void CameraOld::Update()
{

	UpdateDistance();
	if (m_input) {
		UpdateAngleInput();
	}
	else {
		UpdateAngleLerp();
	}
	UpdateCameraPos();

	Vector3 lightVec;

}

void CameraOld::Draw()
{

	printfDx("Camera:hAngle : %4f\n", GetHRadian()*MyMath::ToDegree);
	printfDx("Camera:vAngle : %4f\n", m_transform.rotation.x*MyMath::ToDegree);
	printfDx("Camera:distanceToTarget : %4f\n", m_currentDistance);
	// カメラの視点と注視点の更新
	SetCameraPositionAndTarget_UpVecY(m_transform.position.ToVECTOR(), m_target.position.ToVECTOR());

}

void CameraOld::UpdateDistance()
{

	// カメラの最短距離、最長距離を求める
	float minDistance = kDistanceToTarget - kMinDistance;
	float maxDistance = kDistanceToTarget - kMaxDistance;

	minDistance = MyMath::Clamp(minDistance, 0.0f, kDistanceToTarget);
	maxDistance = MyMath::Clamp(maxDistance, kDistanceToTarget, maxDistance);
	// 距離を指定範囲内に収める
	m_currentDistance = MyMath::Clamp(m_currentDistance, minDistance, maxDistance);
}

void CameraOld::UpdateAngleInput()
{

	float inputRadian = Input::AnalogAngle(Input::Joystick::Right, Pad::Player::P1) * MyMath::ToRadian;

	// 計算用のVECTOR
	Vector3 m_moveVector = { 0.0f,0.0f,0.0f };
	// 入力角度からX,Y方向の移動量を計算
	m_moveVector.x = -sinf(inputRadian);
	m_moveVector.y = -cosf(inputRadian);

	// 正規化
	m_moveVector = m_moveVector.Normalize();
	// 移動量の計算 レバーを倒した割合にかける
	float moveAmount = Input::PadAnalogAmount(Input::Joystick::Right, Pad::Player::P1) * kAngleSpeed;
	// 移動速度をかける
	m_moveVector = (m_moveVector * moveAmount);

	float vAngle = m_transform.rotation.x * MyMath::ToDegree;
	float hAngle = m_transform.rotation.y * MyMath::ToDegree;

	vAngle += m_moveVector.y;
	// 垂直方向の角度を範囲内に収める
	vAngle = MyMath::Clamp(vAngle, kLowAngle, kHighAngle);
	m_transform.rotation.x = vAngle * MyMath::ToRadian;


	hAngle -= m_moveVector.x;
	// 水平方向の角度を範囲内に収める
	hAngle = MyMath::NormalizeAngle(hAngle);
	m_transform.rotation.y = hAngle * MyMath::ToRadian;

	//m_target.position = m_pPlayer->GetPosition();

}

void CameraOld::UpdateAngleLerp()
{
	m_transform.rotation.x = m_target.rotation.x;
	m_transform.rotation.y = m_target.rotation.y;
}

void CameraOld::UpdateCameraPos()
{
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
	rotate *= m_currentDistance;
	Vector3 cameraPos = Vector3(0.0f, kInitCameraHeight, 0.0f);

	cameraPos += m_target.position;
	cameraPos = (cameraPos + rotate);

	m_transform.position = cameraPos;

	m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);



	// 注視点にむかってライトを当てる
	//ChangeLightTypeDir((rotate*-1).Normalize().ToVECTOR());

	//printfDx("target情報\n");
	//printfDx("pos    X : %f | Y : %f | Z : %f\n", m_target.position.x, m_target.position.y, m_target.position.z);
	//printfDx("rotate X : %f | Y : %f | Z : %f\n", m_target.rotation.x, m_target.rotation.y, m_target.rotation.z);
	//printfDx("scale  X : %f | Y : %f | Z : %f\n", m_target.scale.x, m_target.scale.y, m_target.scale.z);

	//printfDx("カメラ情報\n");
	//printfDx("pos    X : %f | Y : %f | Z : %f\n", m_transform.position.x, m_transform.position.y, m_transform.position.z);
	//printfDx("rotate X : %f | Y : %f | Z : %f\n", m_transform.rotation.x, m_transform.rotation.y, m_transform.rotation.z);
	//printfDx("scale  X : %f | Y : %f | Z : %f\n", m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);

}

float CameraOld::CheckAlpha(const Vector3& vec)
{
	float dis = MyMath::Distance(m_transform.position, vec);
	float alpha = dis / kDistance;
	alpha = MyMath::Clamp(alpha, 0.0f, 1.0f);
	return alpha;
}
