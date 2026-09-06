#include"pch.h"

#include "SceneInGameUITest.h"
#include "../SceneTest.h"
#include "../SceneBase.h"
#include "Utility/Vector3.h"
#include "Utility/Color.h"
#include "Utility/GameSetting.h"
#include "Utility/MyRandom.h"
#include "Utility/Loder/Data.h"
#include "Utility/Loder/FromCSV.h"
#include "Utility/Loder/CSVLoader.h"
#include "Utility/Loder/JsonLoader.h"
#include "World/Component/Transform.h"
#include "World/Component/Collision.h"
#include "Camera/CameraOld.h"
#include "Camera/CameraManager.h"
#include "Camera/FollowCamera.h"
#include "Camera/DebugCamera.h"
#include "System/SoundManager.h"
#include "System/FontManager.h"
#include "System/Debug/ProfileScope.h"
#include "System/Debug/Profiler.h"
#include"World/Character/Bee.h"
#include"World/Character/CharacterManager.h"
#include"World/Character/Enemy/Enemy.h"
#include"World/Character/Player/Player.h"
#include"World/Character/Guardian/Dragon.h"
#include"World/Object/Barrier.h"
#include"World/UI/Core/ScreenManager.h"
#include"World/Map/TileManager.h"
#include"World/Map/MapCreate.h"
#include"World/Map/MapManager.h"
#include"World/Object/FloorBlock.h"
#include"World/Object/Item/BlendManager.h"
#include"World/Object/Item/ItemManager.h"
#include"World/Object/Item/ItemObjectManager.h"
#include"world/GameObjectManager.h"
#include"../../World/UI/Screen/IngameHudScreen.h"
#include"../../World/UI/Screen/PauseScreen.h"
#include"../../World/UI/Core/UIInput.h"
#include"../../Scene/SceneSelectDebug.h"
#include"Input/InputManager.h"


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

SceneInGameUITest::SceneInGameUITest() :
	m_pBarrier(nullptr),
	m_pCameraMgr(nullptr),
	m_pDragon(nullptr),
	m_pPlayer(nullptr),
	m_pTileManager(nullptr),
	m_pUIManager(nullptr),
	m_playerNum(0)
{
	// ライトの向きを設定
	Vector3 lightVec = Vector3::YAxis * -1;
	ChangeLightTypeDir(lightVec.ToVECTOR());
	// 最初に接続しているコントローラーの数で初期化
	m_playerNum = 1;


	m_pBarrier = GameObjectManager::GetInstance().CreateObject<Barrier>();
	m_pDragon = GameObjectManager::GetInstance().CreateObject<Dragon>();

	GameObjectManager::GetInstance().CreateObject<Enemy>();
	GameObjectManager::GetInstance().CreateObject<Enemy>();
	GameObjectManager::GetInstance().CreateObject<Enemy>();


	const auto& cameraParam = Data::Csv::LoadCsvAs<FollowCameraParam>(kCameraParamPath);
	//const auto& scameraParam = Data::Json::LoadJsonAs<FollowCameraParam>(kcameraParamPath);


	m_pCameraMgr = std::make_unique<CameraManager>();
	//m_pUiManager = std::make_unique<UIManager>();
	m_pTileManager = std::make_unique<TileManager>();
	m_pPlayer = GameObjectManager::GetInstance().CreateObject<Player>(Vector3::zero);


}

SceneInGameUITest ::~SceneInGameUITest() {}

void SceneInGameUITest::Init() {
	m_pTileManager->Init();
	//m_pPlayer->SetCamera(m_pCamera[0].get());
	//m_pSound->LoadSe();
	//m_pSound->LoadBGM();
	m_pCameraMgr->Init();
	const auto& cameraParam = Data::Csv::LoadCsvAs<FollowCameraParam>(kCameraParamPath);
	m_pCameraMgr->AddCamera(Camera::CameraType::Follow, std::make_unique<FollowCamera>(&m_pPlayer->GetTransform(), cameraParam[0]));
	m_pCameraMgr->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	GameObjectManager::GetInstance().Init();
	m_pDragon->SetMaster(m_pPlayer);
	m_pPlayer->SetBarrier(m_pBarrier);
	//m_pUiManager->SetPlayer(m_pPlayer);
	//m_pUiManager->SetDragon(m_pDragon);
	m_pTileManager->SetPlayer(m_pPlayer);
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());

	m_pUIManager= std::make_unique<ScreenManager>();
	m_pUIManager->PushScreen(std::make_unique<IngameHudScreen>());

	// フェード処理開始
	SceneBase::StartFadeIn();
}

void SceneInGameUITest::End() {
	for (int i = 0; i < m_playerNum; i++) {

		//delete m_pCamera.get();
		//m_pCamera = nullptr;

	}


	//delete m_pGrassMgr.get();			// ポインタの削除
	//m_pGrassMgr = nullptr;			// ポインタをnullptrで初期化

	SoundManager::GetInstance().Release();

	//m_pSound->Release();
	//delete m_pSound;
	//m_pSound = nullptr;

	GameObjectManager::GetInstance().End();
	ItemManager::GetInstance().End();
}

std::unique_ptr<SceneBase> SceneInGameUITest::Update(float deltaTime) {

	// 現在最前面に表示しているのがPauseScreenかどうかチェック
	// 表示していたらポインタ取得

	UI::Command command = m_pUIManager->ConsumeCommand();
	switch (command)
	{
	case UI::Command::ResumeGame:
		break;
	case UI::Command::LoadDebugScene:
		return std::make_unique<SceneSelectDebug>();
		break;
	default:
		break;
	}
	InputData inputData = InputManager::GetInputData();
	m_pUIManager->Update(deltaTime, InputManager::GetInputData());
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	if (inputData.IsPressed(Input::Action::Menu)) {
		m_pUIManager->PushScreen(std::make_unique<PauseScreen>());
	}
	else if (inputData.IsReleased(Input::Action::Menu)) {
		m_pUIManager->PopScreen();
	}

	UpdateInGame(deltaTime, inputData);

	return nullptr;
}

void SceneInGameUITest::UpdateInGame(float deltaTime, InputData inputData)
{
	m_pCameraMgr->Update(deltaTime,inputData);
	ItemManager::GetInstance().SetCameraView(m_pCameraMgr->GetCameraView());
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	//m_pUiManager->Update(deltaTime);
	m_pTileManager->Update(deltaTime, inputData);

	GameObjectManager::GetInstance().Update(deltaTime,inputData);
	ItemManager::GetInstance().Update();

	GameObjectManager::GetInstance().CheckCollision();

}

void SceneInGameUITest::Draw() {
	//DrawGround();
	// カメラの描画
	m_pCameraMgr->Apply();
	// マップの描画処理
	// ゲームオブジェクトの描画処理
	GameObjectManager::GetInstance().Draw();

	m_pTileManager->Draw();
	ItemManager::GetInstance().Draw();
	// ゲージ関連の描画処理
	//m_pUiManager->Draw();
	//m_pHudScreen->Draw();
	//m_pPauseScreen->Draw();
	m_pUIManager->Draw();


}

void SceneInGameUITest::DrawGround()
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


