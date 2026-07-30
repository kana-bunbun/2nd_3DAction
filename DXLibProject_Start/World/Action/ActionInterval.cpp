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
	m_param = ActionIntervalParamManager::GetInstance().GetActionIntervalParam(intervalID);
}

void ActionInterval::Setup()
{
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;
}


void ActionInterval::Update(float deltaTime)
{
	UpdateCount(deltaTime);

	// 効果カウントがインターバルを超えたら効果発動可能
	if (m_intervalCount > m_param.intervalSecond) {
		m_isExecute = true;
	}
}

void ActionInterval::UpdateCount(float deltaTime)
{
	// カウントの更新処理
	m_effectCount = MyMath::Clamp((m_effectCount + deltaTime), 0.0f, m_param.maxSecond);
	// 効果発動のカウントを更新
	m_intervalCount = MyMath::Clamp((m_intervalCount + deltaTime), 0.0f, m_param.intervalSecond);
}

void ActionInterval::Execute()
{
	// カウントのリセット
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;

}

bool ActionInterval::IsFinish()
{
    return m_intervalCount>=m_param.maxSecond;
}
