#pragma once
namespace UI{

	/// <summary>
	/// UImanagerから他のクラスに送る内容をまとめて管理する
	/// </summary>
	enum class Command {
		Invalid = -1,
		None,
		ResumeGame,			// ゲームに戻る
		LoadTitleScene,		// タイトルシーンに戻る
		LoadDebugScene,		// デバッグシーンに戻る
		LoadMainGameScene,	// ゲームシーンに戻る
	};
}
