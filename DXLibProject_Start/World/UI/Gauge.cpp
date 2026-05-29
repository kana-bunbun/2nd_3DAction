#include "Gauge.h"
namespace {
	// valueやmaxで使う基本の値
	constexpr float kDefaultValue = 100;
}
Gauge::Gauge():
m_value(kDefaultValue),
m_max(kDefaultValue),
m_min(0)
{

}

Gauge::Gauge(float max, float value, float min) :
	m_value(max),
	m_max(value),
	m_min(min)
{

}

Gauge::~Gauge()
{

}

void Gauge::Init()
{

}

void Gauge::End()
{

}

void Gauge::Increase(float value)
{
	// 現在の値に加算
	m_value += value;
}

void Gauge::Decrease(float value)
{
	// 現在の値に減算
	m_value -= value;
}

float Gauge::GetValue()
{
	// 現在の値を返す
	return m_value;
}

float Gauge::GetMax()
{
	// 最大値を返す
	return m_max;
}

float Gauge::GetMin()
{
	// 最小値を返す
	return m_min;
}

float Gauge::GetRate()
{
	// 最大値に対する現在の値の割合を返す
	return m_value/m_max;
}

void Gauge::SetValue(float value)
{
	// 現在の値を設定
	m_value = value;
}

void Gauge::SetMax(float max)
{
	// 最大値を設定
	m_max = max;
}

void Gauge::SetMin(float min)
{
	// 最小値を設定
	m_min = min;
}
