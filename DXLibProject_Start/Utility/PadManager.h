#pragma once
class Player;
class ItemCursor;
class TileManager;


/// <summary>
/// コントローラー入力情報の割り当てを管理するクラス
/// </summary>
class PadManager
{
public:
	enum class PadState {// 入力の状態
		Invalid,	// 不正値
		Player,		// プレイヤー操作
		ItemMenu,	// アイテムメニュー操作
		Title,		// タイトル画面操作
		Max,
	};
public:
	PadManager();
	~PadManager();

	void Init();
	void End();
	void Update();

	void ChangePadState(const PadState& padState);

public:
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetItemCursor(ItemCursor* pItemCursor) { m_pItemCursor = pItemCursor; }
	void SetTileManager(TileManager* pTileManager) { m_pTileManager = pTileManager; }
	const PadState& GetPadState() { return m_padState; }
private:
	Player* m_pPlayer;
	ItemCursor* m_pItemCursor;
	TileManager* m_pTileManager;
	PadState m_padState;
};

