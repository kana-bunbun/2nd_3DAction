#pragma once
#include"pch.h"
#include"World/GameObjectParam.h"
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
		/// コリジョンを所持するかどうか
		/// </summary>
		bool hasCollision;

		/// <summary>
		/// コリジョンタグ
		/// </summary>
		CollisionTag collisionTag;

		/// <summary>
		/// コリジョンのパラメータのID
		/// </summary>
		int CollisionParamID;

	};
}
