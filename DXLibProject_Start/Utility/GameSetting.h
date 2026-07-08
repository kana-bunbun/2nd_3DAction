#pragma once

//#include"../Include/Effekseer/EffekseerForDXLib.h"
/// <summary>
/// ゲームの処理関連の初期設定を行う
/// </summary>
class GameSetting
{
public:

	GameSetting() = default;
	~GameSetting() = default;

	/// <summary>
	/// ウィンドウの初期設定
	/// </summary>
	static void InitWindow();

	/// <summary>
	/// DXライブラリでの3D描画の設定
	/// </summary>
	static void InitDxLib3D();


};