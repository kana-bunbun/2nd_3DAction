#include "InputTrigger.h"
namespace {
	// トリガーの最大入力値
	constexpr int kTriggerInputMax = 255;
}

InputTrigger::InputTrigger(int input)
{
	// 入力量を計算
	m_inputRatio = static_cast<float>(input / kTriggerInputMax);
}

