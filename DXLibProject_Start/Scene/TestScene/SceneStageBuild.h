#pragma once
#include "Scene/SceneBase.h"
#include "Utility/Vector3.h"
#include"Input/InputData.h"
#include"World/Component/Collision.h"
#include<memory>
class ScreenManager;
class SceneStageBuild :public SceneBase
{
public:

	/// <summary>
	/// SceneStageBuild画面のコンストラクタ
	/// メンバの初期設定を行う
	/// </summary>
	SceneStageBuild();

	/// <summary>
	/// SceneStageBuild画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneStageBuild();

	/// <summary>
	/// 画面の初期設定を行う
	/// </summary>
	void Init()override;

	/// <summary>
	/// 画面の後処理を行う
	/// </summary>
	void End()override;

	/// <summary>
	/// SceneStageBuild画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理をする画面</returns>
	std::unique_ptr<SceneBase> Update(float deltaTime)override;

	/// <summary>
	/// SceneStageBuild画面の描画を行う
	/// </summary>
	void Draw()override;

private:

	/// <summary>
	/// 位置関係が分かるように地面を線で描画する
	/// </summary>
	void DrawGround();
private:
	/// <summary>
/// スクリーンクラスのポインタ
/// </summary>
	std::unique_ptr<ScreenManager> m_pScreenManager;

};

