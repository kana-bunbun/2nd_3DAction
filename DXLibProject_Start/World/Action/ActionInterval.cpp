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
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;
	m_isActive = false;
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
	// カウントの更新処理
	m_effectCount += deltaTime;
	// 効果発動のカウントを更新
	m_intervalCount += deltaTime;
	// 効果カウントがインターバルを超えたら効果発動可能
	if (m_intervalCount > m_param.intervalSecond) {
		m_intervalCount = m_param.intervalSecond;
		m_isExecute = true;
	}
	// 効果全体のカウントが一定値を超えたら
	if (m_effectCount >= m_param.maxSecond) {
		m_effectCount = m_param.maxSecond;
		m_isActive = false;
	}
}

void ActionInterval::Execute()
{
	// カウントのリセット
	m_intervalCount = 0.0f;
	m_isExecute = false;

}

bool ActionInterval::IsFinish()
{
    return m_effectCount>=m_param.maxSecond;
}
