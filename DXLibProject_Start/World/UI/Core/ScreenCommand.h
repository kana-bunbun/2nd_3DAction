#pragma once

/// <summary>
/// UIManagerから他のクラスに送る内容をまとめて管理する
/// </summary>
enum class ScreenCommand
{
	None,
	ResumeGame,			// ゲーム画面に戻る
	LoadTitleScene,		// タイトル画面に戻る
	LoadDebugScene,		// デバッグシーンに戻る

};
