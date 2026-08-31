#include "DxLib.h"
#include "Utility/Game.h"
#include "Utility/Input.h"
#include "Utility/GameSetting.h"
#include "Scene/SceneManager.h"
#include"Utility/MyRandom.h"
#include"Utility/Color.h"
#include"System/TimeManager.h"
#include"World/UI/BillboardManager.h"
#include"World/Object/Item/BlendManager.h"
#include"System/Debug/Profiler.h"
#include"System/Debug/ProfileScope.h"
#include"System/ActionEffectParamManager.h"
#include"System/CollisionDataManager.h"
#include"System/ResourceManager.h"
#include"Input/InputManager.h"
#include"Input/InputConst.h"
#include<EffekseerForDXLib.h>

#include<memory>

// 追加のインクルードディレクトリ
// 現在Dxライブラリを使用するにあたってC/C++、リンカーにて設定している
// この設定は複数設定して良いもの
// ただし追加しすぎると同じファイル名同氏の競合を起こす危険性があるので使いすぎには注意
// この設定をすることでインクルードの開始地点を増やすことができる
// 

namespace {
	constexpr int kParticleMax = 10000;
}

//========================================================
// WinMain関数　ここからプログラムが始まる
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	GameSetting::InitWindow();

	// Effekseerを使用するためDirectX11を使用
	SetUseDirect3DVersion(DX_DIRECT3D_11);


	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理

		return -1;				// 初期化に失敗したら強制終了
	}

	// Effecseerの初期設定
	// 引数は画面に表示するパーティクルの最大数を設定
	if (Effekseer_Init(kParticleMax) == -1) {
		return -1;
	}

	// ゲーム設定クラスのポインタを生成
	std::unique_ptr<GameSetting> pSetting;
	pSetting = std::make_unique<GameSetting>();

	// ゲームの3Dの初期設定
	pSetting->InitDxLib3D();
	pSetting->InitEffekseer();

	// 乱数の初期化
	MyRandom::Init();
	Input::Init();
	TimeManager::Init();
	BillboardManager::GetInstance().Init();
	BlendManager::GetInstnce().Init();
	InputManager::Init();
	CollisionDataManager::GetInstance();
	ActionEffectParamManager::GetInstance();
	// シーン制御のポインタを生成
	std::unique_ptr<SceneManager> pSceneMgr;
	pSceneMgr = std::make_unique<SceneManager>();

	// シーンの初期化
	pSceneMgr->Init();

	// 描画先を裏面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// メインループ
	while (ProcessMessage() == 0) {
		ClearDrawScreen();		// 画面の初期化
		clsDx();				// デバッグ文字の初期化
		
		Profiler::BeginFrame();
		// 入力更新
		Input::Update();
		TimeManager::Update();
		float deltaTime = TimeManager::GetDeltaTime();
		InputManager::Update(deltaTime);
		


		pSceneMgr->Update(deltaTime);
		
		pSceneMgr->Draw();
		printfDx("deltaItme : %f\n", deltaTime);
		printfDx("rawdeltaItme : %f\n", TimeManager::GetRawDeltaTime());
		printfDx("Fps : %f\n", TimeManager::GetFPS());
		printfDx("timesScale : %f\n", TimeManager::GetTimeScale());
		//Input::Update();
		//Input::Debug();
		Profiler::EndFrame();

		auto records = Profiler::GetRecords();
		int count = 0;
		for (const auto& record : records) {
			count++;
			std::string recordName = record.name;
			std::string recordMs = std::to_string(record.elapsedMilliSecond);
			std::string recordDesc = recordName + " : " + recordMs + "ms";
			DrawString(500, count * 20, recordDesc.c_str(), Color::kRed);
		}

		// 描画先を切り替える
		ScreenFlip();
	}
	ResourceManager::GetInstance().End();
	CollisionDataManager::GetInstance().End();
	ActionEffectParamManager::GetInstance().End();
	pSceneMgr->End();
	Effkseer_End();
	DxLib_End();				// DXライブラリの終了処理
	return 0;					// ソフトの終了 
}

