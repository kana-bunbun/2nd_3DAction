#pragma once
#include "ICollider.h"
#include"Collision.h"
#include"World/GameObjectParam.h"
#include"World/Component/Collision/CollisionShape.h"

namespace Collision{
	class Sphere;
	class AABB;
	class Capsule :public ICollider {
	public:
		Capsule() = default;
		Capsule(const Vector3& start, const Vector3& end, float radius);
		Capsule(const CollisionParam& param);
		~Capsule() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Shape GetShape()const override { return Shape::Capsule; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const ICollider& other)const override;
		/// <summary>
		/// 座標を更新
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override;
		const Vector3& GetStartPosition()const { return m_startPos; }
		const Vector3& GetEndPosition()const { return m_endPos; }
		float GetRadius()const { return m_radius; }
		void SetStartPosition(const Vector3& pos);
		void SetEndPosition(const Vector3& pos);
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPos()const override { return (m_startPos + m_endPos) * 0.5f; }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw(int color = Color::kWhite)const  override;

		/// <summary>
		/// カプセルの半径を設定する関数
		/// </summary>
		/// <param name="radius"></param>
		void SetRadius(float radius);

	private:
		void CheckEndPos();
		Collision::Result CheckSphere(const Collision::Sphere& other)const;
		Collision::Result CheckCapsule(const Collision::Capsule& other)const;
	private:
		Vector3 m_startPos;
		Vector3 m_endPos;
		float m_radius;
	};
}

