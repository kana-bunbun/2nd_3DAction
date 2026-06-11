#pragma once
#include"MapConst.h"
static class ExpantionMethod
{
public:
	static MapConst::eDirectionFour ReverseRirection(MapConst::eDirectionFour direction) {
		int result = static_cast<int>(direction) + 2;
		if (result >= static_cast<int>(MapConst::eDirectionFour::Max)) result -= static_cast<int>(MapConst::eDirectionFour::Max);

		return static_cast<MapConst::eDirectionFour>(result);
	}
};

