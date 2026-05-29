#pragma once
#include"../../Utility/Vector3.h"
#include"Transform.h"
/// <summary>
/// 衝突判定関連のデータや処理
/// </summary>
namespace Collision {


	/// <summary>
	/// 形状データ
	/// </summary>
	enum class Type {
		Sphere,
		Capsule,
		AABB,		// Axis Aligned Bounding Box
		//OBB,		// Oriented Bounding Box

	};

	struct Result {
		/// <summary>
		/// 衝突したかどうか
		/// </summary>
		bool isHit = false;
		/// <summary>
		/// 衝突した面の法線ベクトル
		/// </summary>
		Vector3 normal = Vector3::zero;
		/// <summary>
		/// めり込み具合
		/// どれだぇ押し返すのかに使用したりする
		/// </summary>
		float penetration = 0.0f;

	};

	/// <summary>
	/// 衝突判定の形状の抽象クラス
	/// これを継承し様々な形状で対応できるようにする
	/// </summary>
	class Shape {
	public:
		virtual ~Shape() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		virtual Type GetType()const = 0;
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		virtual Collision::Result CheckCollision(const Shape& other)const = 0;
		/// <summary>
		/// 座標を更新
		/// </summary>
		/// <param name="pos"></param>
		virtual void SetPosition(const Vector3& pos) = 0;
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		virtual Vector3 GetPos()const { return Vector3(); }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		virtual void DebugDraw()const = 0;
	};
	class Sphere :public Shape {
	public:

		Sphere() = default;
		Sphere(const Vector3& pos, float radius) : m_center(pos), m_radius(radius) {}
		~Sphere() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Type GetType()const override { return Type::Sphere; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const Shape& other)const override;
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
		float GetRadus()const { return m_radius; }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw()const  override;
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
	class AABB :public Shape {
	public:
		AABB() = default;
		AABB(const Vector3& center, const Vector3& size);
		~AABB() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Type GetType()const override { return Type::AABB; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const Shape& other)const override;
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
		void DebugDraw()const  override;
	private:
		void SetSize(const Vector3& size);
	private:
		Vector3 m_minPos;
		Vector3 m_maxPos;
		Vector3 m_halfSize;
		Vector3 m_offSet;
	};

	class Capsule :public Shape {
	public:
		Capsule() = default;
		Capsule(const Transform& transform, float radius,float length);
		~Capsule() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		Type GetType()const override { return Type::Capsule; }
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		Collision::Result CheckCollision(const Shape& other)const override;
		/// <summary>
		/// 座標を更新
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos) override;
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetPos()const override { return m_transform.position; }
		/// <summary>
		/// 形状のデバッグ描画
		/// </summary>
		void DebugDraw()const  override;
		/// <summary>
		/// トランスフォームを設定する関数
		/// </summary>
		/// <param name="transform"></param>
		void SetTransform(const Transform& transform);
		/// <summary>
		/// カプセルの半径を設定する関数
		/// </summary>
		/// <param name="radius"></param>
		void SetRadius(float radius);
		/// <summary>
		/// カプセルの長さを設定する関数
		/// </summary>
		/// <param name="length"></param>
		void SetLength(float length);
		/// <summary>
		/// オフセットを設定する関数
		/// </summary>
		/// <param name="offset"></param>
		void SetOffset(float offset) { m_offset = offset; }
	private:
		void CheckEndPos();
	private:
		Vector3 m_minPos;
		Vector3 m_maxPos;
		float m_offset;
		float m_radius;
		float m_length;
		Transform m_transform;
	};

	/// <summary>
	/// 点がAABB内に入っているかどうかを調べる
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool CheckPointInAABB(Collision::AABB& aabb,const Vector3& pos);
}

