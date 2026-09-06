#include"pch.h"
#include "MyMath.h"

Vector3 MyMath::ClosestPointOnSegment(const Vector3& point, const Vector3& start, const Vector3& end)
{
	// 線分のベクトルを用意
	Vector3 segment = end - start;

	// 開始地点から調べたい点の座標へのベクトルを用意
	Vector3 toPoint = point - start;
	// 線分の長さの2乗
	float segmentLengthSq = segment.Dot(segment);
	// 線分の長さが0なら開始地点を返す(startとendが同じ可能性がある)
	if (segmentLengthSq <= Epsilon)return start;
	// pointを線分へ射影した位置を求める
	float t = toPoint.Dot(segment) / segmentLengthSq;
	// 線分の範囲内に収める
	// 飛び出していることがあるで線分の端になるようにする
	t = MyMath::Clamp(t, 0.0f, 1.0f);
	// 最近接点を返す
	return start + segment * t;


}
