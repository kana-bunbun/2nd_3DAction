#pragma once
#include<vector>

class ActionParam;

/// <summary>
/// 発動効果のパラメータを保持しておく
/// </summary>
class ActionParamManager
{
public:
	static ActionParamManager& GetInstance();

	/// <summary>
	/// 発動効果のパラメータ
	/// </summary>
	void Load();
	/// <summary>
	/// ID指定の発動効果取得
	/// </summary>
	const ActionParam& GetActionParam(int ID);
	void End();
private:
	ActionParamManager();
	~ActionParamManager()=default;

	ActionParamManager(const ActionParamManager&) = delete;
	ActionParamManager operator=(const ActionParamManager&) = delete;
	ActionParamManager(ActionParamManager&&) = delete;
	ActionParamManager operator=(const ActionParamManager&&) = delete;
private:
	std::vector<ActionParam> m_actionParam;
};

