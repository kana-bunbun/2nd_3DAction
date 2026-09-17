#include "pch.h"
#include "Capsule.h"
#include "Sphere.h"
#include"Utility/MyMath.h"
namespace Collision {

	Capsule::Capsule(const Vector3& start, const Vector3& end, float radius) :
		m_startPos(start),
		m_endPos(end),
		m_radius(radius)
	{}
	Capsule::Capsule(const CollisionParam& param) :
		m_startPos(param.startPos),
		m_endPos(param.endPos),
		m_radius(param.radius)
	{}
	Collision::Result Capsule::CheckCollision(const ICollider& other) const
	{
		Collision::Result result;
		switch (other.GetShape())
		{
		case Collision::Shape::Sphere: {
			const Collision::Sphere* checkSphere = dynamic_cast<const Collision::Sphere*>(&other);
			result = CheckSphere(*checkSphere);
			break;
		}
		case Collision::Shape::AABB:
			break;
		case Collision::Shape::Capsule:
		{
			result.isHit = false;
			// 判定を調べるためキャストする
			const Capsule* checkCapsule = dynamic_cast<const Capsule*>(&other);

			// カプセル同士の距離を測る
			float length = Segment_Segment_MinLength(
				m_endPos.ToVECTOR(), m_startPos.ToVECTOR(), checkCapsule->m_endPos.ToVECTOR(), checkCapsule->m_startPos.ToVECTOR());

			// 半径の合計を調べる
			float radiusSum = m_radius + checkCapsule->m_radius;
			// カプセル同士の距離が互いの半径の合計より遠いいとき
			if (length > radiusSum)break;
			// カプセル同士の距離が互いの半径の合計より近いとき

			// 当たっている判定
			result.isHit = true;
		}

		break;
		default:
			break;
		}

		return result;
	}
	void Capsule::SetPosition(const Vector3& pos)
	{
		Vector3 center = GetPos();
		Vector3 moveMent = pos - center;
		m_startPos += moveMent;
		m_endPos += moveMent;
	}
	void Capsule::SetStartPosition(const Vector3& pos)
	{
		m_startPos = pos;
	}
	void Capsule::SetEndPosition(const Vector3& pos)
	{
		m_endPos = pos;
	}
	void Capsule::DebugDraw(int color) const
	{
		float debugRadius = m_radius * 0.2f;
		DrawCapsule3D(m_endPos.ToVECTOR(), m_startPos.ToVECTOR(), m_radius, 10, color, color, FALSE);
		DrawSphere3D(m_endPos.ToVECTOR(), debugRadius, 10, Color::kRed, color, TRUE);
		DrawSphere3D(m_startPos.ToVECTOR(), debugRadius, 10, Color::kBlue, color, TRUE);
	}
	void Capsule::SetRadius(float radius)
	{
		m_radius = radius;
	}
	Collision::Result Capsule::CheckSphere(const Sphere& other) const
	{
		Collision::Result result;

		// 球の情報を取得
		Vector3 checkPos = other.GetPos();
		float checkRadius = other.GetRadius();
		// 球とカプセルの最近接点を求める
		Vector3 closestPoint = MyMath::ClosestPointOnSegment(checkPos, m_startPos, m_endPos);
		// 最近接点と球の中心座標のベクトル
		Vector3 dif = closestPoint - checkPos;
		// 中心座標との2乗を取得
		float distanceSquare = dif.GetSqLength();
		// それぞれの半径の合計値を求める
		float radiusSum = m_radius + checkRadius;
		// 衝突しているかどうかチェック
		if (distanceSquare > radiusSum * radiusSum)return result;

		// 当たっていたらresultの作成
		result.isHit = true;

		float distance = dif.GetLength();

		if (distance > MyMath::Epsilon) {
			result.normal = dif / distance;
		}
		else {
			result.normal = Vector3::XAxis;
		}

		// めり込み量を用意
		result.penetration = radiusSum - distance;

		return result;
	}
	Collision::Result Capsule::CheckCapsule(const Capsule& other) const
	{
		return Collision::Result();
	}
}