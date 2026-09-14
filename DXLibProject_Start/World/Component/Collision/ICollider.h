#pragma once

#include"pch.h"
#include"Utility/Color.h"
#include"World/Component/Collision/Collision.h"


namespace Collision {
	/// <summary>
/// 衝突判定の形状の抽象クラス
/// これを継承し様々な形状で対応できるようにする
/// </summary>
	class ICollider {
	public:
		virtual ~ICollider() = default;
		/// <summary>
		/// 形状データを取得する
		/// </summary>
		/// <returns></returns>
		virtual Shape GetType()const = 0;
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <returns></returns>
		virtual Collision::Result CheckCollision(const ICollider& other)const = 0;

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
	
}
