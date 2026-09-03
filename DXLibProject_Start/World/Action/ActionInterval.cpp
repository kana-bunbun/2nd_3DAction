#include "ActionInterval.h"
#include "../../Utility/MyMath.h"
#include "../../System/ActionIntervalParamManager.h"
ActionInterval::ActionInterval()
{

}

ActionInterval::~ActionInterval()
{

}

void ActionInterval::Init(int intervalID)
{
	// 指定されたIDをもとにマネージャーからパラメータを取得
	m_param = ActionIntervalParamManager::GetInstance().GetActionIntervalParam(intervalID);
}

void ActionInterval::Setup()
{
	m_firstCount = 0.0f;
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;
	m_isActive = true;
}


void ActionInterval::Update(float deltaTime)
{
	if (!m_isActive)return;
	UpdateCount(deltaTime);
	printfDx("effectCount   : %f\n", m_effectCount);
	printfDx("intervalCount : %f\n", m_intervalCount);
}

void ActionInterval::UpdateCount(float deltaTime)
{
	if (m_firstCount < m_param.firstInterval) {
		m_firstCount += deltaTime;
		if (m_firstCount >= m_param.firstInterval) {
			m_effectCount = 0.0f;
		}
		else
		return;
	}

	// カウントの更新処理
	m_effectCount += deltaTime;
	// 効果発動のカウントを更新
	m_intervalCount -= deltaTime;
	// 効果カウントがインターバルを超えたら効果発動可能
	if (m_intervalCount <= 0.0f) {
		m_intervalCount = 0.0f;
		m_isExecute = true;
	}
	
	// 最大カウントが不正値の時処理を抜ける
	if (m_param.maxSecond <= 0)return;

	// 効果全体のカウントが一定値を超えたら
	if (m_effectCount >= m_param.maxSecond) {
		Finish();
	}
}

void ActionInterval::ReCount()
{
	// カウントのリセット
	m_intervalCount = m_param.intervalSecond;
	m_isExecute = false;

}

bool ActionInterval::IsFinish()
{
	return m_effectCount>=m_param.maxSecond;
}

void ActionInterval::Finish()
{
	m_effectCount = 0.0f;
	m_isActive = false;
}
