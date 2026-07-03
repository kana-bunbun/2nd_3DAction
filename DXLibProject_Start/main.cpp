#include "DxLib.h"
#include "Utility/Game.h"
#include "Utility/Input.h"
#include "Utility/GameSetting.h"
#include "Scene/SceneManager.h"
#include"Utility/MyRandom.h"
#include"System/TimeManager.h"
#include"World/UI/BillboardManager.h"
#include"World/Object/Item/BlendManager.h"
#include<memory>


//========================================================
// WinMain関数　ここからプログラムが始まる
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	GameSetting::InitWindow();

	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理

		return -1;				// 初期化に失敗したら強制終了
	}

	// ゲーム設定クラスのポインタを生成
	std::unique_ptr<GameSetting> pSetting;
	pSetting = std::make_unique<GameSetting>();

	// ゲームの3Dの初期設定
	pSetting->InitDxLib3D();

	// 乱数の初期化
	MyRandom::Init();
	Input::Init();
	TimeManager::Init();
	BillboardManager::GetInstance().Init();
	BlendManager::GetInstnce().Init();
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

		// 入力更新
		Input::Update();
		TimeManager::Update();
		float deltaTime = TimeManager::GetDeltaTime();
		pSceneMgr->Update(deltaTime);
		
		pSceneMgr->Draw();
		printfDx("deltaItme : %f\n", deltaTime);
		printfDx("rawdeltaItme : %f\n", TimeManager::GetRawDeltaTime());
		printfDx("Fps : %f\n", TimeManager::GetFPS());
		printfDx("timesScale : %f\n", TimeManager::GetTimeScale());
		//Input::Update();
		//Input::Debug();
		// 描画先を切り替える
		ScreenFlip();
	}

	pSceneMgr->End();

	DxLib_End();				// DXライブラリの終了処理
	return 0;					// ソフトの終了 
}

