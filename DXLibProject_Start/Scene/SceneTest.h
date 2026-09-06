#pragma once
#include "SceneBase.h"
#include "Utility/Vector3.h"
#include"Input/InputData.h"
#include"World/Component/Collision.h"
#include<memory>

// スマートポインタ
// 今までのポインタ(生ポインタ)は主導でnew・deleteを行っていた
// スマートポインタはめもり管理を安全に、かつ楽にしてくれるもの 置き換えられるものは置き換え推奨
// スマートポインタは3種類存在する
//	unique_ptr	ユニークポインタ
//	shared_ptr	シェアードポインタ
//	weak_ptr	ウィークポインタ
// 今回はユニークポインタを使う
// unique_ptrは、所有権を1つしか持たず、自動で破棄してくれるポインタのことをいう

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
//
//namespace Collision {
//	class AABB;
//}

namespace {
	constexpr int kCannonNum = 6;
}

/// <summary>
/// 授業で作成して確認用のクラス
/// なにか機能の確認を行うときにこのクラスで検証をする
/// </summary>
class SceneTest : public SceneBase
{
public:

	/// <summary>
	/// SceneTest画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneTest();

	/// <summary>
	/// SceneTest画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneTest();

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

	/// <summary>
	/// Cameraクラスのポインタ
	/// </summary>
	std::unique_ptr<ScreenManager> m_pScreenManager;

};
