#include "pch.h"
#include "Sphere.h"
#include"Utility/MyMath.h"
namespace Collision {
	Sphere::Sphere(const CollisionParam& param) :
		m_center(param.startPos),
		m_radius(param.radius)
	{}

	Collision::Result Sphere::CheckCollision(const ICollider& other) const
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
		{
			// 相手の座標を取得するため
			// Sphereクラスをdynamic_castして派生クラスであるSphereクラスを用意する
			const Sphere* checkSphere = dynamic_cast<const Sphere*>(&other);

			result = CheckSphere(*checkSphere);
			return result;
		}

		case Shape::AABB:
			break;
		case Collision::Shape::Capsule: {

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
		// GetShapeでSphereと取れているため問題ないはずだけど一応
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
}