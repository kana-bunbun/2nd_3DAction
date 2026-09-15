#include "pch.h"
#include "Triangle.h"
#include "Utility/MyMath.h"
namespace Collision {
	Triangle::Triangle(const CollisionParam& param) :
		m_vertex0(param.vertex0),
		m_vertex1(param.vertex1),
		m_vertex2(param.vertex2)
	{}

	Result Collision::Triangle::CheckCollision(const Collision::ICollider& other) const
	{
		return Collision::Result();
	}

	void Triangle::SetPosition(const Vector3& pos)
	{
		// 移動量を求める
		Vector3 move = pos - GetPos();

		// 各頂点に移動量を加算
		m_vertex0 += move;
		m_vertex1 += move;
		m_vertex2 += move;

	}

	Vector3 Triangle::GetPos() const
	{

		return (m_vertex0 + m_vertex1 + m_vertex2) / 3.0f;
	}

	void Triangle::DebugDraw(int color) const
	{
		DrawLine3D(m_vertex0.ToVECTOR(), m_vertex1.ToVECTOR(), color);
		DrawLine3D(m_vertex1.ToVECTOR(), m_vertex2.ToVECTOR(), color);
		DrawLine3D(m_vertex2.ToVECTOR(), m_vertex0.ToVECTOR(), color);
		DrawTriangle3D(m_vertex0.ToVECTOR(), m_vertex1.ToVECTOR(), m_vertex2.ToVECTOR(), color, true);

		// 三角形の重心を取得
		Vector3 center = GetPos();
		// 法線ベクトルを取得
		Vector3 normal = center + GetNormal() * 50;
		DrawLine3D(center.ToVECTOR(), normal.ToVECTOR(), color);
	}

	Vector3 Triangle::GetNormal() const
	{
		// 三角形のある頂点から他の2点へ伸びる辺の外積で求まる

		Vector3 edge1 = m_vertex1 - m_vertex0;
		Vector3 edge2 = m_vertex2 - m_vertex0;
		Vector3 cross = edge1.Cross(edge2);
		if (!cross.GetSqLength())return Vector3::zero;
		return cross.Normalize();
	}
	bool Triangle::IsPointInside(const Vector3& point) const
	{
		// 三角形の内側に点があるかどうか調べる
		// 三角形の3つの辺に対する外積の計算結果がすべて同じ方向を向いていれば点は三角形の内側にある

		// 三角形の辺を用意
		Vector3 edge0 = m_vertex1 - m_vertex0;
		Vector3 edge1 = m_vertex2 - m_vertex1;
		Vector3 edge2 = m_vertex0 - m_vertex2;

		// 各頂点をpointを結ぶ編を用意
		Vector3 toPoint0 = point - m_vertex0;
		Vector3 toPoint1 = point - m_vertex1;
		Vector3 toPoint2 = point - m_vertex2;

		// それぞれに対して外積を求める
		Vector3 crossResult0 = edge0.Cross(toPoint0);
		Vector3 crossResult1 = edge1.Cross(toPoint1);
		Vector3 crossResult2 = edge2.Cross(toPoint2);

		// 三角形の法線取得
		Vector3 normal = GetNormal();

		// 外積の計算結果の向きを法線を用いて内積で確認
		float result0 = crossResult0.Dot(normal);
		float result1 = crossResult1.Dot(normal);
		float result2 = crossResult2.Dot(normal);

		// すべて同じ向きなら内側にある
		return result0 >= -MyMath::Epsilon && result1 >= -MyMath::Epsilon && result2 >= -MyMath::Epsilon;
	}
}
