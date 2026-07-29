#include "ActionInteval.h"
#include "../../Utility/MyMath.h"
#include "../../System/ActionIntervalParamManager.h"
ActionInteval::ActionInteval()
{

}

ActionInteval::~ActionInteval()
{

}

void ActionInteval::Init(int intervalID)
{
	m_param = ActionIntervalParamManager::GetInstance().GetActionIntervalParam(intervalID);
}

void ActionInteval::Setup()
{
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;
}


void ActionInteval::Update(float deltaTime)
{
	UpdateCount(deltaTime);

	// 効果カウントがインターバルを超えたら効果発動可能
	if (m_intervalCount > m_param.intervalSecond) {
		m_isExecute = true;
	}
}

void ActionInteval::UpdateCount(float deltaTime)
{
	// カウントの更新処理
	m_effectCount = MyMath::Clamp((m_effectCount + deltaTime), 0.0f, m_param.maxSecond);
	// 効果発動のカウントを更新
	m_intervalCount = MyMath::Clamp((m_intervalCount + deltaTime), 0.0f, m_param.intervalSecond);
}

void ActionInteval::Execute()
{
	// カウントのリセット
	m_effectCount = 0.0f;
	m_intervalCount = 0.0f;
	m_isExecute = false;

}

bool ActionInteval::IsFinish()
{
    return m_intervalCount>=m_param.maxSecond;
}
