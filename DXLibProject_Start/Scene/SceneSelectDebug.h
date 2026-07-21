#pragma once
#include "SceneBase.h"
#include<memory>
#include<vector>
#include<string>
#include<functional>
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
	std::vector<std::string>m_sceneList;
	
	/// <summary>
	/// 現在選択中のシーン
	/// </summary>
	int m_selectIndex;

};

