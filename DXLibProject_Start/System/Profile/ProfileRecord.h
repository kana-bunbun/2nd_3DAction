#pragma once
#include<string>

namespace Profiler{

	/// <summary>
	/// プロフファイル情報
	/// 1つの処理時間を保持する
	/// </summary>
	struct Record {

		/// <summary>
		/// 計測対象の名前
		/// クラスのインスタンスや関数名を設定
		/// </summary>
		std::string name;

		/// <summary>
		/// 実行時間(ミリ秒)
		/// </summary>
		float elapsedMilliSecond = 0.0f;

	};

}
