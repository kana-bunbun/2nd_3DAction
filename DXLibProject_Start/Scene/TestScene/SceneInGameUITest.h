#pragma once
#include "../SceneBase.h"
#include "../Utility/Vector3.h"
#include "../Utility/Input.h"
#include"../World/Component/Collision.h"
#include<memory>


// 前方宣言
class GameSetting;
class CameraOld;
class CameraManager;
class Player;
class Dragon;
class CharaGaugeManager;
class CharacterManager;
class Bee;
class Barrier;
class UIManager;
class TileManager;
class FloorBlock;
class PadManager;
class GameObjectManager;
class GameObject;
class IngameHudScreen;
class PauseScreen;
class UIManager;


/// <summary>
/// 授業で作成して確認用のクラス
/// なにか機能の確認を行うときにこのクラスで検証をする
/// </summary>
class SceneInGameUITest : public SceneBase
{
public:

	/// <summary>
	/// SceneInGameUITest画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneInGameUITest();

	/// <summary>
	/// SceneTest画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneInGameUITest();

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init()override;

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End()override;

	/// <summary>
	/// SceneTest画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理をする画面</returns>
	std::unique_ptr<SceneBase> Update(float deltaTime)override;
	void UpdateInGame(float deltaTime);
	/// <summary>
	/// SceneTest画面の描画を行う
	/// </summary>
	void Draw()override;

private:

	/// <summary>
	/// 位置関係が分かるように地面を線で描画する
	/// </summary>
	void DrawGround();

private:

	std::unique_ptr<CameraManager> m_pCameraMgr;
	Player* m_pPlayer;
	Dragon* m_pDragon;
	/// <summary>
	/// プレイヤーの数
	/// </summary>
	int m_playerNum;

	Barrier* m_pBarrier;

	std::unique_ptr<TileManager>m_pTileManager;
	std::unique_ptr<PadManager> m_pPadManager;
	std::unique_ptr<UIManager> m_pUIManager;

};
