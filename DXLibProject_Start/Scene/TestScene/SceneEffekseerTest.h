#pragma once
#include "Scene/SceneBase.h"
#pragma once
#include "../SceneBase.h"
#include "Utility/Vector3.h"
#include"Input/InputData.h"
#include"World/Component/Collision.h"
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
class ScreenManager;
class TileManager;
class FloorBlock;
class GameObjectManager;
class GameObject;
class IngameHudScreen;
class PauseScreen;
class ScreenManager;

class SceneEffekseerTest :public SceneBase
{
public:
	SceneEffekseerTest();
	~SceneEffekseerTest();


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
	void UpdateInGame(float deltaTime,InputData inputData);
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
	std::unique_ptr<ScreenManager> m_pUIManager;

	int m_effectResourceHandle;
	int m_playEffectHandle;
	bool m_isEffect;
};
