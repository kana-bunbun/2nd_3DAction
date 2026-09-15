#pragma once
#include "ICollider.h"
namespace Collision {
	class Triangle :public ICollider
	{
	public:
		Triangle() = default;
		Triangle(const Vector3& vertex0, const Vector3& vertex1, const Vector3& vertex2) : m_vertex0(vertex0), m_vertex1(vertex1),m_vertex2(vertex2){}
		Triangle(const CollisionParam& param);
		~Triangle() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Shape GetShape()const override { return Shape::Sphere; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const Collision::ICollider& other)const override;
		/// <summary>
		/// 座標を更新 三角形の重心を更新して各頂点を移動
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override;
		/// <summary>
		/// 三角形の重心の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPos()const override;
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw(int color = Color::kWhite)const  override;

		/// <summary>
		/// 各頂点の座標の取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetVertex0() { return m_vertex0; }
		const Vector3& GetVertex1() { return m_vertex1; }
		const Vector3& GetVertex2() { return m_vertex2; }

		/// <summary>
		/// 3点からなる面の法線の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetNormal()const;
		/// <summary>
		/// 任意の座標が三角形の面の内供部に存在しているかどうか調べる
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		bool IsPointInside(const Vector3& point)const;

	private:
		/// <summary>
		/// 三角形の頂点座標
		/// </summary>
		Vector3 m_vertex0;
		Vector3 m_vertex1;
		Vector3 m_vertex2;
	};
}

