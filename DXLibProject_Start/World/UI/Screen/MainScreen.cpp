#include"pch.h"

#include "MainScreen.h"
#include "../../Object/Barrier.h"
#include "../../Character/Player/Player.h"
#include "../../Character/Enemy/Enemy.h"
#include "../../Character/Guardian/Dragon.h"
#include "../../GameObjectManager.h"
#include "Camera/CameraManager.h"
#include "Camera/FollowCamera.h"
#include "Camera/DebugCamera.h"
#include "Utility/Loader/FromCsv.h"
#include "Utility/Loader/CsvLoader.h"
#include "World/Object/Item/ItemManager.h"
#include "World/Map/TileManager.h"
#include "World/UI/Group/UIItemList.h"
#include "System/Controller/ItemListController.h"
#include "System/Controller/ItemUseController.h"


#include"System/EffectManager.h"
namespace {
	const char* const kCameraParamPath = "CameraParam";
}
MainScreen::MainScreen() :
	m_pCameraMgr(nullptr),
	m_pTileManager(nullptr),
	m_pPlayer(nullptr),
	m_pDragon(nullptr),
	m_pBarrier(nullptr),
	m_pUiItemList(nullptr),
	m_pItemUseController(nullptr)
{
	// ライトの向きを設定
Vector3 lightVec = Vector3::YAxis * -1;
ChangeLightTypeDir(lightVec.ToVECTOR());
}

MainScreen::~MainScreen()
{
	delete m_pUiItemList;
	m_pUiItemList = nullptr;
	delete m_pItemUseController;
	m_pItemUseController = nullptr;
}

void MainScreen::Init()
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
	m_pItemUseController = new ItemUseController(m_pUiItemList);

}

void MainScreen::CreateObjects()
{

	m_pCameraMgr = std::make_unique<CameraManager>();
	m_pTileManager = std::make_unique<TileManager>();

	GameObjectManager::GetInstance().CreateObject<Enemy>();

	m_pCameraMgr->Init();
}

void MainScreen::Update(float deltaTime, const InputData & inputData)
{
	// カメラ更新
	m_pCameraMgr->Update(deltaTime,inputData);
	// カメラの状態をプレイヤーに渡す
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	ItemManager::GetInstance().SetCameraView(m_pCameraMgr->GetCameraView());
	// マップの更新処理
	m_pTileManager->Update(deltaTime, inputData);
	// オブジェクトの更新処理
	GameObjectManager::GetInstance().Update(deltaTime,inputData);
	// オブジェクトの衝突処理
	GameObjectManager::GetInstance().CheckCollision();
	// マップ上にプレイヤーのトランスフォームを設定
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	m_pUiItemList->Update(deltaTime,inputData);
	m_pItemUseController->Update(deltaTime, inputData);

	InputData _inputData = inputData;
	if (_inputData.IsPressed(Input::Action::Dash)) {
		EffectManager::GetInstance().Play(10000, &m_pPlayer->GetTransform());

	}
	EffectManager::GetInstance().Update(deltaTime);
}

void MainScreen::Draw()
{
	// カメラの描画
	m_pCameraMgr->Apply();

	// ゲームオブジェクトの描画処理
	GameObjectManager::GetInstance().Draw();
	ItemManager::GetInstance().Draw();
	// マップの描画処理
	m_pTileManager->Draw();
	m_pUiItemList->Draw();
	EffectManager::GetInstance().Draw();
	ImGui::Begin("Test");
	ImGui::Text("sdfhs");
	ImGui::End();
}
