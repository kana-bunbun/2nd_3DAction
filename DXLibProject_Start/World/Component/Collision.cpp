#include "pch.h"
#include "Collision.h"
#include"../../Utility/Color.h"
#include"../../Utility/MyMath.h"

namespace Collision {
	Collision::Result Sphere::CheckCollision(const Shape& other) const
	{
		// Collision::Result構造体のメンバ変数の値を計算し求める
			// 当たっているかどうか isHit
			// 当たった面の法線ベクトル normal
			// めり込み具合 penetration
		// 求めた結果をreturnで返す
		Collision::Result result;
		switch (other.GetType())
		{
		case Type::Sphere:
		{
			// 相手の座標を取得するため
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
			const Sphere* checkSphere = dynamic_cast<const Sphere*>(&other);

			result = CheckSphere(*checkSphere);
			return result;
		}

		case Type::AABB:
			break;
		case Collision::Type::Capsule: {
			
			const Collision::Capsule* checkCapsule = dynamic_cast<const Collision::Capsule*>(&other);
			result = CheckCapsule(*checkCapsule);
			break;
		}
		default:
			break;
		}
		return result;
	}

	void Sphere::DebugDraw(int color) const
	{

		DrawSphere3D(GetPos().ToVECTOR(), m_radius, 10, color, color, false);
	}

	Collision::Result Sphere::CheckSphere(const Sphere& other) const
	{
		// 相手の座標を取得するため
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
		Collision::Result result;
		// GetTypeでSphereと取れているため問題ないはずだけど一応
		//assert(checkSphere);
		// 球の中心座標から」チェックする球の中心座標を指すベクトルを求める
		Vector3 dif = this->GetPos() - other.GetPos();
		// ベクトルの各成分から距離を三平方の定理で求める
		float distance = (dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z);
		float radiusSum = this->m_radius + other.m_radius;
		// distanceを平方根にせず計算する(平方根の計算は処理負荷が高い)ため
		// 半径の和を2乗する
		radiusSum = radiusSum * radiusSum;
		// もし2つの半径の和がdistanceより短ければ当たっていない
		if (radiusSum <= distance)return result;
		// ここまで来たら当たっている
		result.isHit = true;
		// Resultの情報を求めて格納する

		// 法線
		// 平方のものから正式な距離に変換
		distance = dif.GetLength();

		if (distance > 0.0f) {
			// 法線を格納
			result.normal = dif / distance;
		}
		else {
			// 球の中心座標が完全に一致している場合、0除算が発生するため保険
			result.normal = Vector3::XAxis;
		}

		// めり込み具合
		result.penetration = radiusSum - distance;
		return result;
	}

	Collision::Result Sphere::CheckCapsule(const Capsule& other) const
	{
		Collision::Result result;

		// カプセルの情報を取得
		Vector3 checkStartPos = other.GetStartPosition();
		Vector3 checkEndPos = other.GetEndPosition();
		float checkRadius = other.GetRadius();
		Vector3 myPosition = GetPos();
		// 球とカプセルの最近接点を求める
		Vector3 closestPoint = MyMath::ClosestPointOnSegment(myPosition, checkStartPos, checkEndPos);
		// 最近接点と球の中心座標のベクトル
		Vector3 dif = myPosition - closestPoint;
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
	
	
	
	AABB::AABB(const Vector3& offset, const Vector3& size):
		m_offset(offset)
	{
		SetSize(size);
		//SetPosition(offset);
	}


	Collision::Result AABB::CheckCollision(const Shape& other) const
	{

		// Collision::Result構造体のメンバ変数の値を計算し求める
	// 当たっているかどうか isHit
	// 当たった面の法線ベクトル normal
	// めり込み具合 penetration
	// 求めた結果をreturnで返す
		Collision::Result result;
		switch (other.GetType())
		{
		case Type::Sphere:
			
			break;
		case Type::AABB: 
		{
			// 相手の座標を取得するためAABBクラスをdynamic_castで取得
			const AABB* checkBox = dynamic_cast<const AABB*>(&other);

			// GetTypeでAABBと取れているため問題ないはずだけど一応
			assert(checkBox);

			if (m_maxPos.x<checkBox->m_minPos.x || m_minPos.x>checkBox->m_maxPos.x)return result;
			if (m_maxPos.y<checkBox->m_minPos.y || m_minPos.y>checkBox->m_maxPos.y)return result;
			if (m_maxPos.z<checkBox->m_minPos.z || m_minPos.z>checkBox->m_maxPos.z)return result;

			// ここまで来たら当たっている
			result.isHit = true;

			// 各軸のめり込み具合を調べる
			float overlapX = MyMath::Min(m_maxPos.x, checkBox->m_maxPos.x) - MyMath::Max(m_minPos.x, checkBox->m_minPos.x);
			float overlapY = MyMath::Min(m_maxPos.y, checkBox->m_maxPos.y) - MyMath::Max(m_minPos.y, checkBox->m_minPos.y);
			float overlapZ = MyMath::Min(m_maxPos.z, checkBox->m_maxPos.z) - MyMath::Max(m_minPos.z, checkBox->m_minPos.z);

			// 一番めり込み具合の小さい軸を調べる
			float minOverlap = overlapX;
			Vector3 normal = Vector3::XAxis;


			// 法線を調べる	
			if (overlapY < minOverlap) {
				minOverlap = overlapY;
				normal = Vector3::YAxis;
			}
			if (overlapZ < minOverlap) {
				minOverlap = overlapZ;
				normal = Vector3::ZAxis;
			}

			// めり込み具合を確定
			result.penetration = minOverlap;
			// 法線を調べる
			Vector3 dir = GetPos() - checkBox->GetPos();

			// めり込み量の小さい軸を調べて、向きの+-を設定
			if (normal == Vector3::XAxis) {
				normal.x = (dir.x >= 0.0f) ? 1.0f : -1.0f;
			}
			else if (normal == Vector3::YAxis) {
				normal.y = (dir.y >= 0.0f) ? 1.0f : -1.0f;
			}
			else if (normal == Vector3::ZAxis) {
				normal.z = (dir.z >= 0.0f) ? 1.0f : -1.0f;
			}
			// 調べた法線で確定
			result.normal = normal;
		}
		default:
			break;
		}
		return result;
	}
	void AABB::SetPosition(const Vector3& pos)
	{
		// 中心座標から半分の大きさを足した値
		m_maxPos = pos + m_halfSize + m_offset;
		// 中心座標から半分の大きさを引いた値
		m_minPos = pos - m_halfSize + m_offset;
	}
	void AABB::DebugDraw(int color) const
	{
		Vector3 vertexs[8];
		// 下の面の座標
		vertexs[0] = { m_minPos.x,m_minPos.y,m_minPos.z };
		vertexs[1] = { m_maxPos.x,m_minPos.y,m_minPos.z };
		vertexs[2] = { m_maxPos.x,m_minPos.y,m_maxPos.z };
		vertexs[3] = { m_minPos.x,m_minPos.y,m_maxPos.z };

		// 上の面の座標
		vertexs[4] = { m_minPos.x,m_maxPos.y,m_minPos.z };
		vertexs[5] = { m_maxPos.x,m_maxPos.y,m_minPos.z };
		vertexs[6] = { m_maxPos.x,m_maxPos.y,m_maxPos.z };
		vertexs[7] = { m_minPos.x,m_maxPos.y,m_maxPos.z };

		// 
		DrawLine3D(vertexs[0].ToVECTOR(), vertexs[1].ToVECTOR(), color);
		DrawLine3D(vertexs[1].ToVECTOR(), vertexs[2].ToVECTOR(), color);
		DrawLine3D(vertexs[2].ToVECTOR(), vertexs[3].ToVECTOR(), color);
		DrawLine3D(vertexs[3].ToVECTOR(), vertexs[0].ToVECTOR(), color);
																 
		DrawLine3D(vertexs[4].ToVECTOR(), vertexs[5].ToVECTOR(), color);
		DrawLine3D(vertexs[5].ToVECTOR(), vertexs[6].ToVECTOR(), color);
		DrawLine3D(vertexs[6].ToVECTOR(), vertexs[7].ToVECTOR(), color);
		DrawLine3D(vertexs[7].ToVECTOR(), vertexs[4].ToVECTOR(), color);
																 
		DrawLine3D(vertexs[0].ToVECTOR(), vertexs[4].ToVECTOR(), color);
		DrawLine3D(vertexs[1].ToVECTOR(), vertexs[5].ToVECTOR(), color);
		DrawLine3D(vertexs[2].ToVECTOR(), vertexs[6].ToVECTOR(), color);
		DrawLine3D(vertexs[3].ToVECTOR(), vertexs[7].ToVECTOR(), color);
	}
	void AABB::SetSize(const Vector3& size)
	{
		// 中心座標を保存
		Vector3 center = Vector3(GetPos());
		// サイズを更新
		m_halfSize = size * 0.5f;
		// 中心を使い、最大の座標、最小の座標を更新
		SetPosition(center);
	}
	bool CheckPointInAABB(Collision::AABB& aabb, const Vector3& pos)
	{

		return false;
	}



	Capsule::Capsule(const Vector3& start, const Vector3& end, float radius):
		m_startPos(start),
		m_endPos(end),
		m_radius(radius)
	{
	}
	Collision::Result Capsule::CheckCollision(const Shape & other) const
	{
		Collision::Result result;
		switch (other.GetType())
		{
		case Collision::Type::Sphere: {
			const Collision::Sphere* checkSphere = dynamic_cast<const Collision::Sphere*>(&other);
			result = CheckSphere(*checkSphere);
			break;
		}
		case Collision::Type::AABB:
			break;
		case Collision::Type::Capsule:
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
	void Capsule::SetEndPosition(const Vector3 & pos)
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
