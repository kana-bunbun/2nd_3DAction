#include "pch.h"
#include "StageBuildScreen.h"
#include "../../Object/Barrier.h"
#include "../../Character/Player/Player.h"
#include "../../Character/Enemy/Enemy.h"
#include "../../Character/Guardian/Dragon.h"
#include "../../GameObjectManager.h"
#include "../../Character/CharacterManager.h"
#include "Camera/CameraManager.h"
#include "Camera/FollowCamera.h"
#include "Camera/DebugCamera.h"
#include "Utility/Loader/FromCsv.h"
#include "Utility/Loader/CsvLoader.h"
#include "World/Object/Item/ItemManager.h"
#include "World/Map/TileManager.h"
#include "World/UI/Group/UIItemList.h"
#include"Stage/StageSpawner.h"
#include"Stage/StagePartDatabase.h"
#include"Stage/StageBuilder.h"
#include"World/Object/StagePart.h"
#include"World/Component/Collision/CollisionShape.h"

namespace {
	const char* const kCameraParamPath = "CameraParam";
	constexpr Vector3 kVertex[6] = {
	{-200,-100,-200} ,
	{-200,-100,200} ,
	{200,-100,-200} ,
	{200,-100,200} ,
	{-200,100,400} ,
	{200,100,400} 
	};
}
StageBuildScreen::StageBuildScreen() :
	m_pCameraMgr(nullptr),
	m_pTileManager(nullptr),
	m_pPlayer(nullptr),
	m_pDragon(nullptr),
	m_pBarrier(nullptr),
	m_pUiItemList(nullptr),
	m_pTriangle0(nullptr),
	m_pTriangle1(nullptr),
	m_pTriangle2(nullptr),
	m_pTriangle3(nullptr)
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

	m_pStagePartDatabase->Register("StageBox", { "StageBox", true , CollisionTag::Barrier,10});
	
	StageBuilder builder;

	Stage::StageData stage=builder.BuildStageTest();
	stage = builder.BuildFromJson("StageData");
	m_pStageSpawner->AddStageData(stage);

	Player* player = CharacterManager::GetInstance().GetPlayer();
	if (!player)return;
	Vector3 playerPos = player->GetTransform().position;
	Vector3 vertex0 = { playerPos.x + 50,playerPos.y + 150,playerPos.z+10};
	Vector3 vertex1 = { playerPos.x - 50,playerPos.y - 1,playerPos.z};
	Vector3 vertex2 = { playerPos.x + 150,playerPos.y - 1,playerPos.z};

	m_pSphere = std::make_unique<Collision::Sphere>(m_pPlayer->GetTransform().position, 30);

	m_pTriangle0 = std::make_unique<Collision::Triangle>(kVertex[0], kVertex[1], kVertex[2]);
	m_pTriangle1 = std::make_unique<Collision::Triangle>(kVertex[1], kVertex[3], kVertex[2]);
	m_pTriangle2 = std::make_unique<Collision::Triangle>(kVertex[1], kVertex[4], kVertex[3]);
	m_pTriangle3 = std::make_unique<Collision::Triangle>(kVertex[4], kVertex[5], kVertex[3]);

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

void StageBuildScreen::Update(float deltaTime, const InputData& _inputData)
{
	// カメラ更新
	m_pCameraMgr->Update(deltaTime, _inputData);
	// カメラの状態をプレイヤーに渡す
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	ItemManager::GetInstance().SetCameraView(m_pCameraMgr->GetCameraView());
	// マップの更新処理
	m_pTileManager->Update(deltaTime, _inputData);
	// オブジェクトの更新処理
	GameObjectManager::GetInstance().Update(deltaTime, _inputData);
	// オブジェクトの衝突処理
	GameObjectManager::GetInstance().CheckCollision();
	// マップ上にプレイヤーのトランスフォームを設定
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	m_pUiItemList->Update(deltaTime, _inputData);

	m_pTriangle0->CalcurateClosestPoint(m_pPlayer->GetTransform().position);
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
	
	ImGui::Begin("Test");
	ImGui::Text("sdfhs");
	ImGui::End();
	if(m_pTriangle0)
	m_pTriangle0->DebugDraw();
	if (m_pTriangle1)
		m_pTriangle1->DebugDraw();
	if (m_pTriangle2)
		m_pTriangle2->DebugDraw();
	if (m_pTriangle3)
		m_pTriangle3->DebugDraw();


}
