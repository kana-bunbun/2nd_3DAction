
#include "SceneTest.h"
#include "SceneBase.h"
#include "../Utility/Vector3.h"
#include "../Utility/Input.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../Utility/MyRandom.h"
#include "../World/Component/Transform.h"
#include "../World/Component/Collision.h"
#include "../Camera/CameraOld.h"
#include "../Camera/CameraManager.h"
#include "../Camera/FollowCamera.h"
#include "../Camera/DebugCamera.h"
#include "../System/SoundManager.h"
#include "../System/FontManager.h"
#include"../World/Character/Bee.h"
#include"../World/Character/Player/Player.h"
#include"../World/Character/Guardian/Dragon.h"
#include"../World/Object/Barrier.h"
#include"../World/UI/UIManager.h"
#include"../World/UI/ItemCursor.h"
#include"../World/Character/CharaGaugeManager.h"
#include"../World/Character/Enemy/EnemyManager.h"
#include"../World/Map/TileManager.h"
#include"../World/Map/MapCreate.h"
#include"../World/Map/MapManager.h"
#include"../World/Object/FloorBlock.h"
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
	constexpr int kSize = 50;
	constexpr int kThickness = 50;
}

SceneTest::SceneTest() :
	m_pGameObjectManager(nullptr),
	m_pBarrier(nullptr),
	m_pBee(nullptr),
	m_pCameraMgr(nullptr),
	m_pDragon(nullptr),
	m_pEnemyManager(nullptr),
	m_pGaugeManager(nullptr),
	m_pPlayer(nullptr),
	m_pTileManager(nullptr),
	m_pUiManager(nullptr),
	m_itemCursor(nullptr),
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
	//m_pPlayer = new Player();
	//m_pCamera = new Camera();
	//m_pGrassMgr = new GrassManagerV();
	//for (int i = 0; i < m_playerNum; i++) {
	//	m_pCamera[i] = nullptr;
	//}
	// スマートポインタのインスタンス生成
	// スマートポインタの生成
	// std::make_unique<クラス名>(コンストラクタの引数)
	for (int i = 0; i < m_playerNum; i++) {
		//m_pCamera[i] = std::make_unique<CameraOld>();
		//Input::Pad pp = static_cast<Pad::Player>(i);
		//m_pCamera[i]->SetPad(static_cast<Pad::Player>(i));

	}
	m_pGameObjectManager = std::make_unique<GameObjectManager>();
	m_pBee = m_pGameObjectManager->CreateObject<Bee>();
	m_pBarrier = m_pGameObjectManager->CreateObject<Barrier>();
	m_pDragon = m_pGameObjectManager->CreateObject<Dragon>();
	m_pCameraMgr = std::make_unique<CameraManager>();
	m_pUiManager = std::make_unique<UIManager>();
	m_pGaugeManager = std::make_unique<CharaGaugeManager>();
	m_pEnemyManager = std::make_unique<EnemyManager>();
	m_pTileManager = std::make_unique<TileManager>();
	//m_pFloor = std::make_unique<FloorBlock>();
	// 部屋マスの中でランダムなIDを取得
	randomID = MyRandom::ArrayRandom(MapCreate::GetInstance().GetRooms());
	//取得したマスのIDからマスの座標を計算
	Vector3 initPos = MapManager::GetInstance().GetWorldPosFromID(randomID);
	// ランダムな部屋マスにプレイヤーを生成
	m_pPlayer = m_pGameObjectManager->CreateObject<Player>(initPos);

	m_itemCursor = std::make_unique<ItemCursor>();
}

SceneTest::~SceneTest() {}

void SceneTest::Init() {
	//m_pPlayer->SetCamera(m_pCamera[0].get());
	//m_pSound->LoadSe();
	//m_pSound->LoadBGM();
	m_pPlayer -> Init();
	m_pCameraMgr->Init();
	m_pCameraMgr->AddCamera(Camera::CameraType::Follow,std::make_unique<FollowCamera>(&m_pPlayer->GetTransform()));
	m_pCameraMgr->AddCamera(Camera::CameraType::Debug, std::make_unique<DebugCamera>());
	//m_pCameraMgr->SetActiveCamera(1);
	m_pDragon->SetPlayer(m_pPlayer);
	// シングルトンのSoundManagerでの読み込み
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// m_pSound->PlayBGM(Sound::BGM::Title);
	//SoundManager::GetInstance().PlayBGM(Sound::BGM::Menu);
	m_pBee->Init();
	m_pPlayer->SetBarrier(m_pBarrier);
	m_pDragon->Init();
	m_pUiManager->SetPlayer(m_pPlayer);
	m_pUiManager->SetDragon(m_pDragon);
	m_pGaugeManager->Init();
	m_pGaugeManager->SetPlayer(m_pPlayer);
	m_pGaugeManager->SetDragon(m_pDragon);
	m_pEnemyManager->Init();
	m_pEnemyManager->SetTarget(m_pPlayer);

	//Transform* pos = m_pPlayer->GetTransform();
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());
	m_itemCursor->Init();

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

	//m_pDragon->End();
	//m_pBee->End();
	//m_pUiManager->End();
	//m_pGaugeManager->End();
	//m_pEnemyManager->End();
	//m_pFloor->End();
	m_itemCursor->End();

}

std::unique_ptr<SceneBase> SceneTest::Update(float deltaTime) {
	//m_pCameraMgr->SetTarget(m_pPlayer->GetTransform());
	m_pCameraMgr->Update(deltaTime);
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	//m_pPlayer->Update(deltaTime);
	//m_pBee->Update(deltaTime);
	//m_pBarrier->Update(deltaTime);
	m_pUiManager->Update(deltaTime);
	//m_pDragon->Update(deltaTime);
	m_pGaugeManager->Update();
	//m_pEnemyManager->Update(deltaTime);
	//m_pFloor->Update(deltaTime);
	m_pTileManager->Update(deltaTime);
	if (m_pGameObjectManager) {
		m_pGameObjectManager->Update(deltaTime);
	}
	m_itemCursor->Update(deltaTime);

	// 敵と当たっているかどうかを調べる
	Collision::Result result = m_pBee->GetCollision().CheckCollision(m_pPlayer->GetCollision());
	printfDx("当たってい%s\n", result.isHit ? "る" : "ない");
	m_pPlayer->ResolveCollision(*m_pBee, result);


	if (Input::IsPressed(Input::Button::RT, Input::Pad::P1)) {
	if (Input::IsDown(Input::Button::LT, Input::Pad::P1))
		m_pDragon->Call(m_pBee);
	else
		m_pDragon->CallBack();
	}
	if (Input::IsDown(Input::Button::LT, Input::Pad::P1))
		m_pPlayer->SetCameraAngle(m_pBee->GetTransform().position);
	if (Input::IsPressed(Input::Button::RThumb, Input::Pad::P1)) {
		m_pCameraMgr->NextCamera();
		bool isDebug = m_pCameraMgr->GetActiveCameraType() == Camera::CameraType::Follow;
		m_pPlayer->SetActive(isDebug);
		m_pDragon->SetActive(isDebug);
		m_pBarrier->SetActive(isDebug);
		m_pBee->SetActive(isDebug);
	}

	Collision::AABB aabb = Collision::AABB(Vector3::zero, Vector3(300, 300, 300));
	aabb.DebugDraw();
	result = aabb.CheckCollision(m_pPlayer->GetCollision());
	//m_pPlayer->ResolveCollision(GameObject::CollisionTag::Wall, result);

	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());

	// シーン遷移処理
	//if (シーン切り替えの条件) {
	// return std::make_unique<遷移させたいシーン>();
	//}
	result = m_pTileManager->CheckCollision(m_pPlayer);
	//m_pPlayer->ResolveCollision(GameObject::CollisionTag::Wall, result);
	if (Input::IsPressed(Input::Button::B, Input::Pad::P1)) {
		if (m_pTileManager->IsUpStair()) {
		m_pTileManager->SetUpFloor();
		// 部屋マスの中でランダムなIDを取得
		randomID = MyRandom::ArrayRandom(MapCreate::GetInstance().GetRooms());
		//取得したマスのIDからマスの座標を計算
		Vector3 initPos = MapManager::GetInstance().GetWorldPosFromID(randomID);
		// ランダムな部屋マスにプレイヤーを生成
		m_pPlayer ->SetFirstPos(initPos);
		}
	}

	if (IsFading()) {
			m_pPlayer->m_pad = Input::Pad::Invalid;
	}
	else if (Input::IsPressed(Input::Button::Y, Input::Pad::P1)) {
		if (m_pPlayer->m_pad == Input::Pad::Invalid) {
			m_pPlayer->m_pad = Input::Pad::P1;
		}
		else {
			m_pPlayer->m_pad = Input::Pad::Invalid;
		}
	}
	else {
			m_pPlayer->m_pad = Input::Pad::P1;
	}

	if (m_pGameObjectManager) {
	}
	return nullptr;
}

void SceneTest::Draw() {
	DrawGround();

	m_pCameraMgr->Apply();
	if (m_pGameObjectManager) {
		m_pGameObjectManager->Draw();
		// m_pFloor->Draw();
		// m_pBee->Draw();
		// m_pDragon->Draw();
		// m_pPlayer->Draw();
		// m_pBarrier->Draw();
	}

		 m_pEnemyManager->Draw();
		 m_pTileManager->Draw();
		 m_pUiManager->Draw();
		 m_itemCursor->Draw();

	int handle = FontManager::GetInstance().GetFontHandle(kFontName, kSize, kThickness);
	printfDx("randomID : %d\n", randomID);

	// ビルボードの描画
	// ビルボードで描画する座標を用意
	Vector3 billboardTarget = Vector3(400.0f, 50.0f, -400.0f);

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


