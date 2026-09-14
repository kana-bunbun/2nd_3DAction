#pragma once
#include"Collision.h"
#include"ICollider.h"
#include"World/GameObjectParam.h"
#include"Sphere.h"
#include"Capsule.h"
#include"World/Component/Collision/Sphere.h"
#include"World/Component/Collision/Capsule.h"

namespace Collision {
	
	class AABB :public ICollider {
	public:
		AABB() = default;
		AABB(const Vector3& center, const Vector3& size);
		AABB(const CollisionParam& param);
		~AABB() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Shape GetType()const override { return Shape::AABB; }
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
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPos()const override { return (m_minPos + m_maxPos) * 0.5f; }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw(int color = Color::kWhite)const  override;
	private:
		void SetSize(const Vector3& size);
	private:
		Vector3 m_minPos;
		Vector3 m_maxPos;
		Vector3 m_halfSize;
		Vector3 m_offset;
	};

}

