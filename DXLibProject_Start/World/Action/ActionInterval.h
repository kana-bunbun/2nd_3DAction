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
	/// <summary>
	/// 外部から呼ぶ終了処理
	/// </summary>
	void Finish();
	/// <summary>
	/// 効果発動可能か
	/// </summary>
	/// <returns></returns>
	bool IsExecute() { return m_isExecute; }
	/// <summary>
	/// 発動効果が開始しているかどうか
	/// </summary>
	/// <returns></returns>
	bool IsActive() { return m_isActive; }

	void SetActive(bool active) { m_isActive = active; }
private:
	/// <summary>
	/// インターバルのパラメータ
	/// </summary>
	ActionIntervalParam m_param;
	/// <summary>
	/// 最初に効果を発動するまでのカウント
	/// </summary>
	float m_firstCount;
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
	/// <summary>
	/// アクティブかどうか
	/// </summary>
	bool m_isActive;
};

