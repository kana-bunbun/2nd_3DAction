
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
#include"../World/Character/CharaGaugeManager.h"
#include"../World/Character/Enemy/EnemyManager.h"
#include"../World/Map/TileManager.h"
#include"../World/Map/MapCreate.h"
#include"../World/Map/MapManager.h"
#include"../World/Object/FloorBlock.h"
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
		Pad::Player pp = static_cast<Pad::Player>(i);
		//m_pCamera[i]->SetPad(static_cast<Pad::Player>(i));

	}
	m_pBee = std::make_unique<Bee>();
	m_pBarrier = std::make_unique<Barrier>();
	m_pUiManager = std::make_unique<UIManager>();
	m_pDragon = std::make_unique<Dragon>();
	m_pCameraMgr = std::make_unique<CameraManager>();
	m_pGaugeManager = std::make_unique<CharaGaugeManager>();
	m_pEnemyManager = std::make_unique<EnemyManager>();
	m_pTileManager = std::make_unique<TileManager>();
	m_pFloor = std::make_unique<FloorBlock>();

	// 部屋マスの中でランダムなIDを取得
	std::vector<int>roomID = MapCreate::GetInstance().GetRooms();
	randomID = roomID[MyRandom::Int(0, roomID.size() - 1)];
	//取得したマスのIDからマスの座標を計算
	Vector3 initPos = MapManager::GetInstance().GetWorldPosFromID(randomID);
	// ランダムな部屋マスにプレイヤーを生成
	m_pPlayer = std::make_unique<Player>(initPos);
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
	m_pDragon->SetPlayer(m_pPlayer.get());
	// シングルトンのSoundManagerでの読み込み
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// m_pSound->PlayBGM(Sound::BGM::Title);
	//SoundManager::GetInstance().PlayBGM(Sound::BGM::Menu);
	m_pBee->Init();
	m_pPlayer->SetBarrier(m_pBarrier.get());
	m_pDragon->Init();
	m_pUiManager->SetPlayer(m_pPlayer.get());
	m_pUiManager->SetDragon(m_pDragon.get());
	m_pGaugeManager->Init();
	m_pGaugeManager->SetPlayer(m_pPlayer);
	m_pGaugeManager->SetDragon(m_pDragon);
	m_pEnemyManager->Init();
	m_pEnemyManager->SetTarget(m_pPlayer.get());

	m_pFloor->Init();

	//Transform* pos = m_pPlayer->GetTransform();
	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());

	// フェード処理開始
	SceneBase::StartFadeIn();

}

void SceneTest::End() {
	for (int i = 0; i < m_playerNum; i++) {

		//delete m_pCamera.get();
		//m_pCamera = nullptr;

	}
	m_pDragon->End();


	//delete m_pGrassMgr.get();			// ポインタの削除
	//m_pGrassMgr = nullptr;			// ポインタをnullptrで初期化

	SoundManager::GetInstance().Release();

	//m_pSound->Release();
	//delete m_pSound;
	//m_pSound = nullptr;
	m_pBee->End();
	m_pUiManager->End();
	m_pGaugeManager->End();
	m_pEnemyManager->End();
	m_pFloor->End();

}

std::unique_ptr<SceneBase> SceneTest::Update(float deltaTime) {
	//m_pCameraMgr->SetTarget(m_pPlayer->GetTransform());
	m_pCameraMgr->Update(deltaTime);
	m_pPlayer->SetCameraView(m_pCameraMgr->GetCameraView());
	m_pPlayer->Update(deltaTime);
	m_pBee->Update(deltaTime);
	m_pBarrier->Update(deltaTime);
	m_pUiManager->Update(deltaTime);
	m_pDragon->Update(deltaTime);
	m_pGaugeManager->Update();
	m_pEnemyManager->Update(deltaTime);
	m_pFloor->Update(deltaTime);

	// 敵と当たっているかどうかを調べる
	Collision::Result result = m_pBee->GetCollision().CheckCollision(m_pPlayer->GetCollision());
	printfDx("当たってい%s\n", result.isHit ? "る" : "ない");
	m_pPlayer->ResolveCollision(*m_pBee, result);

	Collision::Result hitFloor = m_pFloor->GetCollision().CheckCollision(m_pPlayer->GetCollision());
	m_pPlayer->ResolveCollision(*m_pFloor, result);

	if (Input::IsPressed(Input::Button::RT, Pad::Player::P1)) {
	if (Input::IsDown(Input::Button::LT, Pad::Player::P1))
		m_pDragon->Call(m_pBee.get());
	else
		m_pDragon->CallBack();
	}
	if (Input::IsDown(Input::Button::LT, Pad::Player::P1))
		m_pPlayer->SetCameraAngle(m_pBee->GetTransform().position);
	if (Input::IsPressed(Input::Button::RThumb, Pad::Player::P1)) {
		m_pCameraMgr->NextCamera();
		bool isDebug = m_pCameraMgr->GetActiveCameraType() == Camera::CameraType::Follow;
		m_pPlayer->SetActive(isDebug);
		m_pDragon->SetActive(isDebug);
		m_pBarrier->SetActive(isDebug);
		m_pBee->SetActive(isDebug);
	}


	m_pTileManager->SetMarkPos(m_pPlayer->GetTransform());

	// シーン遷移処理
	//if (シーン切り替えの条件) {
	// return std::make_unique<遷移させたいシーン>();
	//}
	m_pTileManager->CheckCollision(m_pPlayer.get());
	if (Input::IsPressed(Input::Button::Back, Pad::Player::P1)) {
		if(m_pTileManager->IsUpStair())
		m_pTileManager->SetUpFloor();
	}



	return nullptr;
}

void SceneTest::Draw() {
	printfDx("パッドの数：%d\n", m_playerNum);
	// プレイヤーの数だけ繰り返す
	for (int i = 0; i < m_playerNum; i++) {
		DrawGround();
		SetDrawArea(Game::kScreenWidth / m_playerNum*i, 0, Game::kScreenWidth / m_playerNum * (i+1), Game::kScreenHeight);
		printfDx("Pad::Player->%d\n",i);
		SetCameraScreenCenter(Game::kScreenWidth / (m_playerNum * 2) * ((i * 2)+1), Game::kScreenHeight / 2);
	
		m_pCameraMgr->Apply();
		m_pFloor->Draw();

		m_pEnemyManager->Draw();
		m_pBee->Draw();
		m_pDragon->Draw();
		m_pPlayer->Draw();
		m_pBarrier->Draw();
		DrawBox(Game::kScreenWidth / m_playerNum * i - 1, 0, Game::kScreenWidth / m_playerNum * i + 1, Game::kScreenHeight, Color::kBlack, TRUE);
		m_pTileManager->Draw();
		m_pUiManager->Draw();
	}
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


