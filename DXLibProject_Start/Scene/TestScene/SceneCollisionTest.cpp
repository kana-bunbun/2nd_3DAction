#include"pch.h"
#include "SceneCollisionTest.h"
#include "../SceneSelectDebug.h"

#include"Utility/Color.h"
#include"Utility/MyMath.h"
#include"Input/InputData.h"
#include"Input/InputManager.h"
#include"Camera/CameraManager.h"
#include"Camera/DebugCamera.h"

namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

	const char* const kFontName = "Ink Free";
	constexpr int kFontSize = 50;
	constexpr int kFontThickness = 50;

	const char* const kCameraParamPath = "CameraParam";
}
SceneCollisionTest::SceneCollisionTest():
	m_pCameraManager(nullptr)
{
	m_pCameraManager = std::make_unique<CameraManager>();
	m_pCameraManager->Init();
	m_pCameraManager->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());
	m_pCameraManager->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());
	m_pCameraManager->SetActiveCamera(Camera::CameraType::Debug);
	SceneBase::StartFadeIn();
}

void SceneCollisionTest::Init()
{
    // フェード処理開始
    SceneBase::StartFadeIn();
}

void SceneCollisionTest::End()
{

}

std::unique_ptr<SceneBase> SceneCollisionTest::Update(float deltaTime)
{
	InputData inputData = InputManager::GetInputData();
    if (inputData.IsPressed(Input::Action::Menu))
        return std::make_unique<SceneSelectDebug>();

	m_pCameraManager->Update(deltaTime,inputData);
    return nullptr;
}

void SceneCollisionTest::Draw()
{
    DrawString(130, 130, "CollisionTest", Color::kWhite);
	m_pCameraManager->Apply();
	DrawGround();
}

void SceneCollisionTest::DrawGround()
{
	Vector3 pos1;
	Vector3 pos2;

	pos1 = Vector3(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = Vector3(-kLineAreaSize / 2.0f, 0.0f, kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1.ToVECTOR(), pos2.ToVECTOR(), Color::kWhite);
		pos1.x += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.x += kLineAreaSize / static_cast<float>(kLineNum);
	}

	pos1 = Vector3(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = Vector3(kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		DrawLine3D(pos1.ToVECTOR(), pos2.ToVECTOR(), Color::kWhite);
		pos1.z += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.z += kLineAreaSize / static_cast<float>(kLineNum);
	}
}
