#pragma once
class ImguiManager
{
public:
	/// <summary>
	/// 初期設定 プログラム起動時に実行
	/// </summary>
	void Init();
	/// <summary>
	/// 毎フレームの最初に呼ぶ
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// 毎フレームの最後に呼ぶ
	/// </summary>
	void EndFrame();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Release();

private:

	/// <summary>
	/// DXライブラリのマウス入力をimguiに渡す
	/// </summary>
	void UpdateMouseInput();

};

