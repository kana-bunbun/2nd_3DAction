
#include "SceneTest.h"
#include "SceneBase.h"
#include "../Utility/Vector3.h"
#include "../Utility/Input.h"
#include "../Utility/Color.h"
#include "../Utility/GameSetting.h"
#include "../World/Component/Transform.h"
#include "../World/Component/Collision.h"
#include "../Camera/Camera.h"
#include "../System/SoundManager.h"
#include"../World/Character/Bee.h"
#include"../World/Character/Player/Player.h"
#include<cassert>
#include <math.h>
#include<memory>
#include<DxLib.h>

namespace {

	constexpr float kLineAreaSize = 10000.0f;	// 地面を描画する線のエリアの大きさ
	constexpr int kLineNum = 50;				// 地面を描画する線の数

	// ビルボードで使用する画像のファイルパス
	const char* const kBillBoardDataPath = ".\\Resource\\image\\DxLogo.png";

	constexpr Vector3 kInitGrassPos = { 0.0f, 0.0f, -400.0f };	// 草の初期座標

}

SceneTest::SceneTest() :
	m_playerNum(0)
{
	// 最初に接続しているコントローラーの数で初期化
	m_playerNum = GetJoypadNum();
	// コントローラー接続が失敗していたら警告
	if (!m_playerNum) {

		assert(false && "コントローラー 接続失敗");
	}
	//m_pPlayer = new Player();
	//m_pCamera = new Camera();
	//m_pGrassMgr = new GrassManagerV();
	for (int i = 0; i < m_playerNum; i++) {
		m_pCamera[i] = nullptr;
	}
	// スマートポインタのインスタンス生成
	// スマートポインタの生成
	// std::make_unique<クラス名>(コンストラクタの引数)
	for (int i = 0; i < m_playerNum; i++) {
		m_pCamera[i] = std::make_unique<Camera>();
		Pad::Player pp = static_cast<Pad::Player>(i);
		m_pCamera[i]->SetPad(static_cast<Pad::Player>(i));

	}
	m_pPlayer = std::make_unique<Player>();
	m_pBee = std::make_unique<Bee>();
}

SceneTest::~SceneTest() {}

void SceneTest::Init() {
	m_pPlayer->SetCamera(m_pCamera[0].get());
	//m_pSound->LoadSe();
	//m_pSound->LoadBGM();
	m_pPlayer -> Init();
	m_pCamera[0]->Init(m_pPlayer.get());

	// シングルトンのSoundManagerでの読み込み
	SoundManager::GetInstance().LoadBGM();
	SoundManager::GetInstance().LoadSe();

	// m_pSound->PlayBGM(Sound::BGM::Title);
	//SoundManager::GetInstance().PlayBGM(Sound::BGM::Menu);
	m_pBee->Init();
}

void SceneTest::End() {
	for (int i = 0; i < m_playerNum; i++) {

		m_pCamera[i]->End();
		//delete m_pCamera.get();
		//m_pCamera = nullptr;

	}


	//delete m_pGrassMgr.get();			// ポインタの削除
	//m_pGrassMgr = nullptr;			// ポインタをnullptrで初期化

	SoundManager::GetInstance().Release();

	//m_pSound->Release();
	//delete m_pSound;
	//m_pSound = nullptr;
	m_pBee->End();
}

SceneBase* SceneTest::Update() {
	m_pPlayer->Update();
	m_pCamera[0]->SetTarget(m_pPlayer->GetTransform());
	m_pCamera[0]->Update();

	m_pBee->Update();
	return this;
}

void SceneTest::Draw() {
	printfDx("パッドの数：%d\n", m_playerNum);
	// プレイヤーの数だけ繰り返す
	for (int i = 0; i < m_playerNum; i++) {
		DrawGround();
		SetDrawArea(Game::kScreenWidth / m_playerNum*i, 0, Game::kScreenWidth / m_playerNum * (i+1), Game::kScreenHeight);
		printfDx("Pad::Player->%d\n",i);
		SetCameraScreenCenter(Game::kScreenWidth / (m_playerNum * 2) * ((i * 2)+1), Game::kScreenHeight / 2);
	
		m_pCamera[i]->Draw();
	
		m_pBee->Draw();

		DrawBox(Game::kScreenWidth / m_playerNum * i - 1, 0, Game::kScreenWidth / m_playerNum * i + 1, Game::kScreenHeight, Color::kBlack, TRUE);
	}
	m_pPlayer->Draw();
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


