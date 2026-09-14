#pragma once
#include"pch.h"
#include"Utility/Vector3.h"


namespace Collision {


	/// <summary>
	/// 形状データ
	/// </summary>
	enum class Shape {
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

}