#pragma once
#include<string>
#include"../../Data/ActionIntervalParam.h"
#include<functional>
/// <summary>
///  効果発動のタイミングを指示する
/// </summary>
class ActionInterval
{
public:
	ActionInterval();
	~ActionInterval();
	/// <summary>
	/// IDを指定し、インターバルのパラメータを設定する
	/// </summary>
	/// <param name="intervalID">インターバルパラメータのID</param>
	void Init(int intervalID);
	/// <summary>
	/// カウントのリセット
	/// </summary>
	void Setup();

	void Update(float deltaTime);
	void UpdateCount(float deltaTime);
	/// <summary>
	/// 効果発動処理
	/// </summary>
	void Execute();

	/// <summary>
	/// 発動効果が終了しているかどうか
	/// </summary>
	bool IsFinish();
private:
	/// <summary>
	/// インターバルのパラメータ
	/// </summary>
	ActionIntervalParam m_param;
	/// <summary>
	/// 効果が発動してからのカウント
	/// </summary>
	float m_effectCount;
	/// <summary>
	///	効果の発動間隔
	/// </summary>
	float m_intervalCount;
	/// <summary>
	/// 効果発動可能かどうか
	/// </summary>
	bool m_isExecute;
};

