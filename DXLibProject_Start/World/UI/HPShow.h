#pragma once
#include "GaugeShow.h"
class HPShow :public GaugeShow
{
public:
	HPShow()=default;
	HPShow(const Vector3& position);
	~HPShow();
};

