#pragma once
#include"Scene/SceneBase.h"
#include"Utility/Vector3.h"
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
class PadManager;
class GameObjectManager;
class GameObject;
#include"System/EffectResourceManager.h"
#include"System/EffectManager.h"

class SceneEffekseerTest  : public SceneBase
{
public:

	/// <summary>
	/// SceneEffekseerTest  画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneEffekseerTest ();

	/// <summary>
	/// SceneEffekseerTest  画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneEffekseerTest ();

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init()override;

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End()override;

	/// <summary>
	/// SceneEffekseerTest  画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理をする画面</returns>
	std::unique_ptr<SceneBase> Update(float deltaTime)override;

	/// <summary>
	/// SceneEffekseerTest  画面の描画を行う
	/// </summary>
	void Draw()override;

private:

	/// <summary>
	/// 位置関係が分かるように地面を線で描画する
	/// </summary>
	void DrawGround();

private:

	/// <summary>
	/// Cameraクラスのポインタ
	/// </summary>
	std::unique_ptr<ScreenManager> m_pScreenManager;

	std::unique_ptr<EffectResourceManager>m_pEffectResourceManager;
	std::unique_ptr<EffectManager>m_pEffectManager;
};
