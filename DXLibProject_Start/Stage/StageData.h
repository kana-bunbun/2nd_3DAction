#pragma once
#include"pch.h"
#include"World/Component/Transform.h"


namespace Stage{

	/// <summary>
	/// ステージ上に登場するオブジェクト1つ分のステージデータ
	/// </summary>
	struct ObjectData {

		/// <summary>
		/// StagePart名
		/// </summary>
		std::string partName;

		/// <summary>
		/// シーン上のトランスフォーム
		/// </summary>
		Transform transform;

	};

	/// <summary>
	/// ステージ全体の配置データ
	/// </summary>
	struct StageData {
		std::vector<ObjectData>objects;
	};

}
