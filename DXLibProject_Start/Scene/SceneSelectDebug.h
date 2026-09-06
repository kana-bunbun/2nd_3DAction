#pragma once
#include"pch.h"
#include "SceneBase.h"
#include<functional>

// 関数オブジェクトとは、関数を変数のように扱うことができるオブジェクト
// 整数の情報を扱うとき
// int num = 0; ← numという整数を扱う変数の箱を用意
// 関数オブジェクトの構文
// std::function<戻り値(引数)> 関数オブジェクト名;
// std::function<void()> function; ←functionという関数を扱う箱を用意
// 
// この関数オブジェクトの使用時に以下のメリットがある
// ・「あとで」実行する処置をデータのように扱える
// ・処理を入れ替えられる(UI実装時に効果が発揮できる)
// ・依存関係を逆転できる
// 
// 過度な使用に注意、そこで何をしているのかが追いづらくなる
// 特に関数オブジェクトの中に関数オブジェクトのような形は避けるべき
// ここではUIやイベントのみの使用にとどめることを意識しながら使用する

class SceneSelectDebug : public SceneBase
{
public:
	struct SceneInfo {
	public:
		// シーンの名前
		std::string name;
		// 関数オブジェクト
		// SceneBaseクラスのユニークポインタを返すCreateSceneFunc
		std::function<std::unique_ptr<SceneBase>()>createScenefunc;
	};
public:
	SceneSelectDebug();
	~SceneSelectDebug()override = default;

	void Init()override;
	void End()override;
	std::unique_ptr<SceneBase> Update(float deltaTime)override;
	void Draw()override;


private:
	/// <summary>
	/// 接続するシーンのリスト
	/// </summary>
	std::vector<SceneInfo>m_sceneList;
	
	/// <summary>
	/// 現在選択中のシーン
	/// </summary>
	int m_selectIndex;

};

