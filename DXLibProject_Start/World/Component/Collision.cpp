#include "Collision.h"

#include<cassert>
#include<DxLib.h>
#include"../../Utility/Color.h"
#include"../../Utility/MyMath.h"

namespace Collision {
	// 球-----------------------------------------------------------------------------------
	Collision::Result Sphere::CheckCollision(const Shape& other) const
	{
		// Collision::Resultを使わない場合の球同士の当たり判定
		/*
		// 当たった形状が球なら
		switch(other.GetType()) {
		case Type::Sphere:
			// 相手の座標を取得するため
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
			const Sphere* checkSphere = dynamic_cast<const Sphere*>(&other);

			// GetTypeでSphereと取れているため問題ないはずだけど一応
			//assert(checkSphere);
			// 球の中心座標から」チェックする球の中心座標を指すベクトルを求める
			Vector3 dif = this->GetPos() - checkSphere->GetPos();
			// ベクトルの各成分から距離を三平方の定理で求める
			float distance = (dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z);
			float radiusSum = this->m_radius + checkSphere->m_radius;
			// distanceを平方根にせず計算する(平方根の計算は処理負荷が高い)ため
			// 半径の和を2乗する
			radiusSum = radiusSum* radiusSum;
			if (distance <= radiusSum) {
				printfDx("d");
			}
			// もし2つの判定の和がdistanceより短ければ当たっている
			return(distance <= radiusSum);

		return false;
		}
		*/

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

			// GetTypeでSphereと取れているため問題ないはずだけど一応
			//assert(checkSphere);
			// 球の中心座標から」チェックする球の中心座標を指すベクトルを求める
			Vector3 dif = this->GetPos() - checkSphere->GetPos();
			// ベクトルの各成分から距離を三平方の定理で求める
			float distance = (dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z);
			float radiusSum = this->m_radius + checkSphere->m_radius;
			// distanceを平方根にせず計算する(平方根の計算は処理負荷が高い)ため
			// 半径の和を2乗する
			radiusSum = radiusSum * radiusSum;
			// もし2つの判定の和がdistanceより短ければ当たっている
			if (distance <= radiusSum)return result;
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

		case Type::AABB:
			
		default:
			break;
		}
		return result;
	}

	void Sphere::DebugDraw() const
	{

		DrawSphere3D(GetPos().ToVECTOR(), m_radius, 10, Color::kWhite, Color::kWhite, false);
	}
	// 球-----------------------------------------------------------------------------------

	AABB::AABB(const Vector3& offset, const Vector3& size):
		m_offSet(offset)
	{
		SetSize(size);
		SetPosition(offset);
	}

	// AABB---------------------------------------------------------------------------------
	Collision::Result AABB::CheckCollision(const Shape& other) const
	{
/*
		// 形状がAABBなら
		if (other.GetType() != Collision::Type::AABB)return false;
		// 相手の座標を取得するためAABBクラスをdynamic_castで取得
		const AABB* checkBox = dynamic_cast<const AABB*>(&other);

		// GetTypeでAABBと取れているため問題ないはずだけど一応
		assert(checkBox);

		if (m_maxPos.x<checkBox->m_minPos.x || m_minPos.x>checkBox->m_maxPos.x)return false;
		if (m_maxPos.y<checkBox->m_minPos.y || m_minPos.y>checkBox->m_maxPos.y)return false;
		if (m_maxPos.z<checkBox->m_minPos.z || m_minPos.z>checkBox->m_maxPos.z)return false;

		// ここまで来たら当たっている
		return true;
		*/
		// Collision::Result構造体のメンバ変数の値を計算し求める
	// 当たっているかどうか isHit
	// 当たった面の法線ベクトル normal
	// めり込み具合 penetration
	// 求めた結果をreturnで返す
		Collision::Result result;
		switch (other.GetType())
		{
		case Type::Sphere:
			// 相手の座標を取得するため
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
			/*const Sphere* checkSphere = dynamic_cast<const Sphere*>(&other);

			// GetTypeでSphereと取れているため問題ないはずだけど一応
			//assert(checkSphere);
			// 球の中心座標から」チェックする球の中心座標を指すベクトルを求める
			Vector3 dif = this->GetPos() - checkSphere->GetPos();
			// ベクトルの各成分から距離を三平方の定理で求める
			float distance = (dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z);
			float radiusSum = this->m_radius + checkSphere->m_radius;
			// distanceを平方根にせず計算する(平方根の計算は処理負荷が高い)ため
			// 半径の和を2乗する
			radiusSum = radiusSum * radiusSum;
			// もし2つの判定の和がdistanceより短ければ当たっている
			if (distance <= radiusSum)return result;
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
			*/
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
				normal.x = (dir.x <= 0.0f) ? 1.0f : -1.0f;
			}
			else if (normal == Vector3::YAxis) {
				normal.y = (dir.y <= 0.0f) ? 1.0f : -1.0f;
			}
			else if (normal == Vector3::ZAxis) {
				normal.z = (dir.z <= 0.0f) ? 1.0f : -1.0f;
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
		m_maxPos = pos + m_halfSize + m_offSet;
		// 中心座標から半分の大きさを引いた値
		m_minPos = pos - m_halfSize + m_offSet;
	}
	void AABB::DebugDraw() const
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
		DrawLine3D(vertexs[0].ToVECTOR(), vertexs[1].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[1].ToVECTOR(), vertexs[2].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[2].ToVECTOR(), vertexs[3].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[3].ToVECTOR(), vertexs[0].ToVECTOR(), Color::kWhite);

		DrawLine3D(vertexs[4].ToVECTOR(), vertexs[5].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[5].ToVECTOR(), vertexs[6].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[6].ToVECTOR(), vertexs[7].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[7].ToVECTOR(), vertexs[4].ToVECTOR(), Color::kWhite);

		DrawLine3D(vertexs[0].ToVECTOR(), vertexs[4].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[1].ToVECTOR(), vertexs[5].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[2].ToVECTOR(), vertexs[6].ToVECTOR(), Color::kWhite);
		DrawLine3D(vertexs[3].ToVECTOR(), vertexs[7].ToVECTOR(), Color::kWhite);
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



	Cupsule::Cupsule(const Transform& transform, float radius, float length) :
		m_minPos(),
		m_maxPos(),
		m_radius(radius),
		m_length(length),
		m_transform(transform)
	{
		

	}
	Collision::Result Cupsule::CheckCollision(const Shape & other) const
	{
		return Collision::Result();
	}
	void Cupsule::SetPosition(const Vector3& pos)
	{
		m_transform.position = pos;
	}
	void Cupsule::DebugDraw() const
	{
		DrawCapsule3D(m_maxPos.ToVECTOR(), m_minPos.ToVECTOR(), m_radius, 10, Color::kWhite, Color::kWhite, FALSE);
		DrawSphere3D(m_maxPos.ToVECTOR(), 20, 10, Color::kRed, Color::kRed, TRUE);
		DrawSphere3D(m_minPos.ToVECTOR(), 20, 10, Color::kBlue, Color::kBlue, TRUE);
	}
	void Cupsule::SetTransform(const Transform& transform)
	{
		m_transform = transform;
		CheckEndPos();
	}
	void Cupsule::SetRadius(float radius)
	{
		m_radius = radius;
		CheckEndPos();
	}
	void Cupsule::SetLength(float length)
	{
		m_length = length;
		CheckEndPos();
	}
	void Cupsule::CheckEndPos()
	{
		// 水平方向の成分
		float sinHol = -sinf(m_transform.rotation.y);
		float cosHol = -cosf(m_transform.rotation.y);
		// 垂直方向の成分
		float sinVer = -sinf(m_transform.rotation.x+DX_PI_F*0.5f);
		float cosVer = -cosf(m_transform.rotation.x + DX_PI_F * 0.5f);

		// ベクトルの計算
		Vector3 rotate;
		rotate.x = cosVer * sinHol;
		rotate.y = sinVer;
		rotate.z = cosVer * cosHol;

		Vector3 offsetVec = rotate * m_offset;
		// オフセットを考慮したカプセルの二点を計算
		m_maxPos = (m_transform.position - rotate*m_length) - offsetVec;
		m_minPos = (m_transform.position + rotate*m_length) - offsetVec;


	}
}
