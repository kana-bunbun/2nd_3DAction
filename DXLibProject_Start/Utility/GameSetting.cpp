#include"pch.h"

#include "GameSetting.h"
#include "../Utility/Vector3.h"
#include "Game.h"


namespace {
	constexpr int BackGroundR=112/*128*/;
	constexpr int BackGroundG=128/*229*/;
	constexpr int BackGroundB=128/*256*/;
}

void GameSetting::InitWindow()
{
	// ウィンドウ名を設定
	SetMainWindowText(Game::kWindowText);

	// ウィンドウサイズを指定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBit);

	// ウィンドウモードで起動
	ChangeWindowMode(Game::kWindowMode);

}

void GameSetting::InitDxLib3D()
{
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

	// 確認用に背景色を設定
	SetBackgroundColor(BackGroundR, BackGroundG, BackGroundB);
}

void GameSetting::InitEffekseer()
{
	// フルスクリーンウィンドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(false);
	// DXライブラリのデバイスロストをした時のコールバックを設定
	// ウィンドウとフルスクリーンの切り替えが発生する場合は必ず実行する
	// ただし、DirectX11を使用する際は実行する必要はない
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// 後はDXライブラリのカメラとEffekseerのカメラを同期する必要がある
	// ↑はここではなく、CameraManagerで行う

}

