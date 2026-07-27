#pragma once
#include"../../Utility/Vector3.h"
#include"../../Utility/Color.h"
#include"Transform.h"
#include"../GameObjectParam.h"

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
		virtual void DebugDraw(int color = Color::kWhite)const = 0;
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
		void DebugDraw(int color = Color::kWhite)const  override;
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
		void DebugDraw(int color = Color::kWhite)const  override;
	private:
		void SetSize(const Vector3& size);
	private:
		Vector3 m_minPos;
		Vector3 m_maxPos;
		Vector3 m_halfSize;
		Vector3 m_offset;
	};

	class Capsule :public Shape {
	public:
		Capsule() = default;
		Capsule(const Vector3& start,const Vector3& end,float radius);
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
	private:
		Vector3 m_startPos;
		Vector3 m_endPos;
		float m_radius;
	};

	/// <summary>
	/// 点がAABB内に入っているかどうかを調べる
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool CheckPointInAABB(Collision::AABB& aabb,const Vector3& pos);
}

