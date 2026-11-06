#pragma once
#include<vector>
#include"ProfileRecord.h"

/// <summary>
/// 計測結果を保存する処理を記載
/// </summary>
namespace Profiler {

	/// <summary>
	/// 計測開始
	/// </summary>
	void BeginFrame();

	/// <summary>
	/// 計測終了
	/// </summary>
	void EndFrame();

	/// <summary>
	/// 計測結果を追加
	/// </summary>
	/// <param name="record"></param>
	void AddRecord(const Record& record);

	/// <summary>
	/// 計測結果の一覧を取得
	/// </summary>
	/// <returns></returns>
	const std::vector<Record>& GetRecords();
}
