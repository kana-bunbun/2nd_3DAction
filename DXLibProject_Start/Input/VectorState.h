#pragma once
#include"InputConst.h"
#include"Utility/Vector2.h"
class VectorState {
public:
	VectorState() {}
	VectorState(Vector2 vector, float radian, float ratio);
	Vector2 GetVector() { return vector; }
	const float GetRadian() { return radian; }
	const float GetRatio() { return ratio; }
private:
	Vector2 vector = Vector2::zero;
	float radian=0.0f;
	float ratio=0.0f;
};