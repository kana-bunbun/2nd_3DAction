#include "Gauge.h"
namespace {
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
	m_value += value;
}

void Gauge::Decrease(float value)
{
	m_value -= value;
}

float Gauge::GetValue()
{
	return m_value;
}

float Gauge::GetMax()
{
	return m_max;
}

float Gauge::GetMin()
{
	return m_min;
}

float Gauge::GetRate()
{
	return m_value/m_max;
}

void Gauge::SetValue(float value)
{
	m_value = value;
}

void Gauge::SetMax(float max)
{
	m_max = max;
}

void Gauge::SetMin(float min)
{
	m_min == min;
}
