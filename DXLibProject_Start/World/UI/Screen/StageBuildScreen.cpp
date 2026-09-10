#include "pch.h"
#include "StageBuildScreen.h"
#include "../../Object/Barrier.h"
#include "../../Character/Player/Player.h"
#include "../../Character/Enemy/Enemy.h"
#include "../../Character/Guardian/Dragon.h"
#include "../../GameObjectManager.h"
#include "Camera/CameraManager.h"
#include "Camera/FollowCamera.h"
#include "Camera/DebugCamera.h"
#include "Utility/Loder/FromCsv.h"
#include "Utility/Loder/CsvLoader.h"
#include "World/Object/Item/ItemManager.h"
#include "World/Map/TileManager.h"
#include "World/UI/Group/UIItemList.h"
#include"Stage/StageSpawner.h"
#include"Stage/StagePartDatabase.h"
#include"World/Object/StagePart.h"

namespace {
	const char* const kCameraParamPath = "CameraParam";
}
StageBuildScreen::StageBuildScreen() :
	m_pCameraMgr(nullptr),
	m_pTileManager(nullptr),
	m_pPlayer(nullptr),
	m_pDragon(nullptr),
	m_pBarrier(nullptr),
	m_pUiItemList(nullptr)
{
	// ライトの向きを設定
	Vector3 lightVec = Vector3::YAxis * -1;
	ChangeLightTypeDir(lightVec.ToVECTOR());
}

StageBuildScreen::~StageBuildScreen()
{

}

void StageBuildScreen::Init()
{
	// オブジェクト生成
	CreateObjects();
	// キャラクター生成
	m_pDragon = GameObjectManager::GetInstance().CreateObject<Dragon>();
	m_pPlayer = GameObjectManager::GetInstance().CreateObject<Player>(Vector3::zero);
	m_pBarrier = GameObjectManager::GetInstance().CreateObject<Barrier>();

	m_pDragon->SetMaster(m_pPlayer);
	m_pPlayer->SetBarrier(m_pBarrier);
	// カメラの初期設定
	const auto& cameraParam = Data::Csv::LoadCsvAs<FollowCameraParam>(kCameraParamPath);
	m_pCameraMgr->AddCamera(Camera::CameraType::Follow, std::make_unique<FollowCamera>(&m_pPlayer->GetTransform(), cameraParam[0]));
	m_pCameraMgr->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());

	GameObjectManager::GetInstance().Init();
	m_pTileManager->Init();

	m_pUiItemList = new UIItemList();
	m_pUiItemList->Init();

	m_pStagePartDatabase = std::make_unique<StagePartDatabase>();
	m_pStageSpawner = std::make_unique<StageSpawner>(*m_pStagePartDatabase);

	m_pStagePartDatabase->Register("TestBlock", { "StageBoxModel", CollisionTag::Barrier, false });
	
	Stage::StageData stage;
	Vector3 playerPos = m_pPlayer->GetTransform().position;
	for (int i = 0; i < 10; i++) {
		Vector3 randomPos = Vector3(MyRandom::Float01(),MyRandom::Float01() ,MyRandom::Float01())*350;
		stage.objects.push_back({ "TestBlock", { {playerPos + randomPos},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f} } });
	}
	m_pStageParts = m_pStageSpawner->SpawnStage(stage);
}

void StageBuildScreen::CreateObjects()
{

	m_pCameraMgr = std::make_unique<CameraManager>();
	m_pTileManager = std::make_unique<TileManager>();

	GameObjectManager::GetInstance().CreateObject<Enemy>();
	GameObjectManager::GetInstance().CreateObject<Enemy>();
	GameObjectManager::GetInstance().CreateObject<Enemy>();

	m_pCameraMgr->Init();
}

void StageBuildScreen::Update(float deltaTime, const InputData& inputData)
{
	// カメラ更新
	m_pCameraMgr->Update(deltaTime, inputData);
	// カメラの状態をプレイヤーに渡す
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	ItemManager::GetInstance().SetCameraView(m_pCameraMgr->GetCameraView());
	// マップの更新処理
	m_pTileManager->Update(deltaTime, inputData);
	// オブジェクトの更新処理
	GameObjectManager::GetInstance().Update(deltaTime, inputData);
	// オブジェクトの衝突処理
	GameObjectManager::GetInstance().CheckCollision();
	// マップ上にプレイヤーのトランスフォームを設定
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	m_pUiItemList->Update(deltaTime, inputData);

	for (auto& part : m_pStageParts) {
		part->Update(deltaTime, inputData);
	}
}

void StageBuildScreen::Draw()
{
	// カメラの描画
	m_pCameraMgr->Apply();

	// ゲームオブジェクトの描画処理
	GameObjectManager::GetInstance().Draw();
	ItemManager::GetInstance().Draw();
	// マップの描画処理
	m_pTileManager->Draw();
	m_pUiItemList->Draw();
	
	for (auto& part : m_pStageParts) {
	part->Draw();
	}

	ImGui::Begin("Test");
	ImGui::Text("sdfhs");
	ImGui::End();
}
