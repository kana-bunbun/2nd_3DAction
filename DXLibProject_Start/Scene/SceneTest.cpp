
#include "SceneTest.h"
#include "SceneBase.h"
#include "../Utility/Vector3.h"
#include "../Utility/Input.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../Utility/MyRandom.h"
#include "../Utility/PadManager.h"
#include "../Utility/Data.h"
#include "../World/Component/Transform.h"
#include "../World/Component/Collision.h"
#include "../Camera/CameraOld.h"
#include "../Camera/CameraManager.h"
#include "../Camera/FollowCamera.h"
#include "../Camera/DebugCamera.h"
#include "../System/SoundManager.h"
#include "../System/FontManager.h"
#include"../World/Character/Bee.h"
#include"../World/Character/CharacterManager.h"
#include"../World/Character/Enemy/Enemy.h"
#include"../World/Character/Player/Player.h"
#include"../World/Character/Guardian/Dragon.h"
#include"../World/Object/Barrier.h"
#include"../World/UI/UIManager.h"
#include"../World/UI/ItemCursor.h"
#include"../World/Character/CharaGaugeManager.h"
#include"../World/Map/TileManager.h"
#include"../World/Map/MapCreate.h"
#include"../World/Map/MapManager.h"
#include"../World/Object/FloorBlock.h"
#include"../World/Object/Item/BlendManager.h"
#include"../world/GameObjectManager.h"
#include<cassert>
#include<memory>
#include<DxLib.h>

namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

	const char* const kFontName = "Ink Free";
	constexpr int kFontSize = 50;
	constexpr int kFontThickness = 50;

	const char* const kTestPath = "Data\\test.csv";
}

SceneTest::SceneTest() :
	m_pGameObjectManager(nullptr),
	m_pBarrier(nullptr),
	m_pBee(nullptr),
	m_pCameraMgr(nullptr),
	m_pDragon(nullptr),
	m_pGaugeManager(nullptr),
	m_pPlayer(nullptr),
	m_pTileManager(nullptr),
	m_pUiManager(nullptr),
	m_pItemCursor(nullptr),
	m_pPadManager(nullptr),
	m_pCharacterManager(nullptr),
	m_playerNum(0)
{
	// ライトの向きを設定
	Vector3 lightVec= Vector3::YAxis*-1;
	ChangeLightTypeDir(lightVec.ToVECTOR());
	// 最初に接続しているコントローラーの数で初期化
	m_playerNum = GetJoypadNum();
	// コントローラー接続が失敗していたら警告
	if (!m_playerNum) {

		assert(false && "コントローラー 接続失敗");
	}
	
	m_pGameObjectManager = std::make_unique<GameObjectManager>();
	m_pBee = m_pGameObjectManager->CreateObject<Bee>();
	m_pBarrier = m_pGameObjectManager->CreateObject<Barrier>();
	m_pDragon = m_pGameObjectManager->CreateObject<Dragon>();
	m_pGameObjectManager->CreateObject<Enemy>();
	m_pGameObjectManager->CreateObject<Enemy>();
	m_pGameObjectManager->CreateObject<Enemy>();
	m_pCameraMgr = std::make_unique<CameraManager>();
	m_pUiManager = std::make_unique<UIManager>();
	m_pGaugeManager = std::make_unique<CharaGaugeManager>();
	m_pPadManager= std::make_unique<PadManager>();
	m_pTileManager = std::make_unique<TileManager>();
	m_pCharacterManager = std::make_unique<CharacterManager>();
	m_pTileManager->SetGameObjectManager(m_pGameObjectManager.get());
	m_pTileManager->SetCharacterManager(m_pCharacterManager.get());
	m_pCharacterManager->SetGameObjectManager(m_pGameObjectManager.get());
	m_pPlayer = m_pGameObjectManager->CreateObject<Player>();

	m_pItemCursor = std::make_unique<ItemCursor>();
}

SceneTest::~SceneTest() {}

void SceneTest::Init() {
	m_pTileManager->Init();
	//m_pPlayer->SetCamera(m_pCamera[0].get());
	//m_pSound->LoadSe();
	//m_pSound->LoadBGM();
	m_pCameraMgr->Init();
	m_pCameraMgr->AddCamera(Camera::CameraType::Follow,std::make_unique<FollowCamera>(&m_pPlayer->GetTransform()));
	m_pCameraMgr->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	m_pGameObjectManager->Init();
	m_pDragon->SetPlayer(m_pPlayer);
	m_pPlayer->SetBarrier(m_pBarrier);
	m_pUiManager->SetPlayer(m_pPlayer);
	m_pUiManager->SetDragon(m_pDragon);
	m_pGaugeManager->Init();
	m_pGaugeManager->SetPlayer(m_pPlayer);
	m_pGaugeManager->SetDragon(m_pDragon);
	m_pPadManager->SetPlayer(m_pPlayer);
	m_pPadManager->SetItemCursor(m_pItemCursor.get());
	m_pPadManager->SetTileManager(m_pTileManager.get());
	m_pPadManager->Init();
	m_pTileManager->SetPlayer(m_pPlayer);
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	m_pItemCursor->Init();


	// フェード処理開始
	SceneBase::StartFadeIn();
}

void SceneTest::End() {
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
	if (m_pGameObjectManager) {
		m_pGameObjectManager->End();
	}

	m_pItemCursor->End();
	m_pPadManager->End();

}

std::unique_ptr<SceneBase> SceneTest::Update(float deltaTime) {
	m_pCameraMgr->Update(deltaTime);
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	m_pUiManager->Update(deltaTime);
	m_pGaugeManager->Update();
	m_pTileManager->Update(deltaTime);
	if (m_pGameObjectManager) {
		m_pGameObjectManager->Update(deltaTime);
	}
	m_pItemCursor->Update();
	m_pPadManager->Update();

	m_pGameObjectManager->CheckCollision();
	// 敵と当たっているかどうかを調べる
	//Collision::Result result = m_pBee->GetCollision().CheckCollision(m_pPlayer->GetCollision());
	//printfDx("当たってい%s\n", result.isHit ? "る" : "ない");
	//m_pPlayer->ResolveCollision(*m_pBee, result);


	if (Input::IsPressed(Input::Button::RT, Input::Pad::P1)) {
		if (Input::IsDown(Input::Button::LT, Input::Pad::P1)) {
		//m_pDragon->Call(m_pGameObjectManager->FindObject<Enemy>());
		}
	else
		m_pDragon->CallBack();
	}
	// カメラ切り替え処理
	//if (Input::IsPressed(Input::Button::RThumb, Input::Pad::P1)) {
	//	m_pCameraMgr->NextCamera();
	//	bool isDebug = m_pCameraMgr->GetActiveCameraType() == Camera::CameraType::Follow;
	//	m_pPlayer->SetActive(isDebug);
	//	m_pDragon->SetActive(isDebug);
	//	m_pBarrier->SetActive(isDebug);
	//	m_pBee->SetActive(isDebug);
	//}


	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	
	
	// フェード中はコントローラー入力情報をだれにも渡さない
	if (IsFading()) {
		m_pPadManager->ChangePadState(PadManager::PadState::Invalid);
	}
	// フェードイン終了直後はコントローラー入力情報をプレイヤーに渡す
	else if(IsFadeEnd()){
		m_pPadManager->ChangePadState(PadManager::PadState::Player);
	}

	if (m_pGameObjectManager) {
	}
	return nullptr;
}

void SceneTest::Draw() {
	DrawGround();
	// カメラの描画
	m_pCameraMgr->Apply();
	// マップの描画処理
	// ゲームオブジェクトの描画処理
	if (m_pGameObjectManager) {
		m_pGameObjectManager->Draw();
	}
	m_pTileManager->Draw();

	// アイテムメニュー中は画面を少し暗くする
	if (m_pPadManager->GetPadState() == PadManager::PadState::ItemMenu) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kBlack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// ゲージ関連の描画処理
	m_pUiManager->Draw();
	// アイテムスロットの更新処理
	m_pItemCursor->Draw();

	int handle = FontManager::GetInstance().GetFontHandle(kFontName, kFontSize, kFontThickness);
	printfDx("randomID : %d\n", randomID);
	BlendManager::GetInstnce().Debug();
}

void SceneTest::DrawGround()
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


