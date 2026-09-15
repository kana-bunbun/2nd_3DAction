#include "pch.h"
#include "AABB.h"
#include"Utility/MyMath.h"

namespace Collision {


	AABB::AABB(const Vector3& offset, const Vector3& size) :
		m_offset(offset)
	{
		SetSize(size);
		//SetPosition(offset);
	}

	AABB::AABB(const CollisionParam& param) :
		m_offset(param.startPos)
	{
		SetSize(param.size);
	}


	Collision::Result AABB::CheckCollision(const ICollider& other) const
	{

		// Collision::Result構造体のメンバ変数の値を計算し求める
	// 当たっているかどうか isHit
	// 当たった面の法線ベクトル normal
	// めり込み具合 penetration
	// 求めた結果をreturnで返す
		Collision::Result result;
		switch (other.GetShape())
		{
		case Shape::Sphere:

			break;
		case Shape::AABB:
		{
			// 相手の座標を取得するためAABBクラスをdynamic_castで取得
			const AABB* checkBox = dynamic_cast<const AABB*>(&other);

			// GetShapeでAABBと取れているため問題ないはずだけど一応
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
}