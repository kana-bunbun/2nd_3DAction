#pragma once
#include"InputConst.h"
#include"Utility/Vector2.h"
struct VectorState {
	const Vector2 GetVector() { return vector; }
	const float GetRadian() { return radian; }
	const float GetRatio() { return ratio; }
	Vector2 vector = Vector2::Zero;
	float radian=0.0f;
	float ratio=0.0f;
};