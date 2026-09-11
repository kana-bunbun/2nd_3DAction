#pragma once
#include"pch.h"
#include"World/GameObjectParam.h"
#include"World/Component/Collision.h"
namespace Stage{

	/// <summary>
	/// StageのPartの設定データ
	/// モデルやコリジョンデータを設定する
	/// </summary>
	struct PartData
	{
		/// <summary>
		/// パーツの名前
		/// </summary>
		std::string modelName;

		/// <summary>
		/// コリジョンタグ
		/// </summary>
		CollisionTag collisionTag;

		/// <summary>
		/// コリジョンを所持するかどうか
		/// </summary>
		bool hasCollision;
	};
}
