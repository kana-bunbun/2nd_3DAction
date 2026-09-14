#pragma once
#include "Collision.h"
#include "ICollider.h"
#include"World/GameObjectParam.h"
#include"World/Component/Collision/CollisionShape.h"

namespace Collision {
	class Sphere :public ICollider {
	public:

		Sphere() = default;
		Sphere(const Vector3& pos, float radius) : m_center(pos), m_radius(radius) {}
		Sphere(const CollisionParam& param);
		~Sphere() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Shape GetType()const override { return Shape::Sphere; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const Collision::ICollider& other)const override;
		/// <summary>
		/// 座標を更新
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override { m_center = pos; }
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPos()const override { return m_center; }
		/// <summary>
		/// 半径の取得
		/// </summary>
		/// <returns></returns>
		float GetRadius()const { return m_radius; }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw(int color = Color::kWhite)const  override;
		Collision::Result CheckSphere(const Collision::Sphere& other)const;
		Collision::Result CheckCapsule(const Collision::Capsule& other)const;

	private:
		/// <summary>
		/// 球の中心座標
		/// </summary>
		Vector3 m_center;
		/// <summary>
		/// 球の半径
		/// </summary>
		float m_radius;
	};
}