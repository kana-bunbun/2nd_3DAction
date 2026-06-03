#include "DxLib.h"
#include "Utility/Game.h"
#include "Utility/Input.h"
#include "Utility/GameSetting.h"
#include "Scene/SceneManager.h"
#include"Utility/MyRandom.h"
#include"Utility/Time.h"
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
	GameSetting* pSetting;
	pSetting = new GameSetting();

	// ゲームの3Dの初期設定
	pSetting->InitDxLib3D();

	// 乱数の初期化
	MyRandom::Init();

	Time::GetInstance();

	// シーン制御のポインタを生成
	SceneManager* pSceneMgr;
	pSceneMgr = new SceneManager();

	// シーンの初期化
	pSceneMgr->Init();

	// 描画先を裏面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while (ProcessMessage() == 0) {

		Time::GetInstance().Update();	// 現在のカウントを取得

		ClearDrawScreen();		// 画面の初期化
		clsDx();				// デバッグ文字の初期化

		pSceneMgr->Update();
		pSceneMgr->Draw();
#ifdef _DEBUG
		printfDx("FPS %f\n", 1.0f / Time::GetInstance().GetDeltaTime());
		printfDx("deltaTime %f\n",Time::GetInstance().GetDeltaTime());
		/*PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		printfDx("Memory %d MB\n", pmc.WorkingSetSize / 1024 / 1024);*/
#endif

		//Input::Update();
		//Input::Debug();
		// 描画先を切り替える
		ScreenFlip();
		// FPS調整
		// 1フレームあたりの経過時間が経過するため待機
		Time::GetInstance().WaitProcess();
	}

	pSceneMgr->End();

	DxLib_End();				// DXライブラリの終了処理
	return 0;					// ソフトの終了 
}

