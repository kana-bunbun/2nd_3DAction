#include "ProfileScope.h"

#include"pch.h"
#include "ProfileRecord.h"
#include "Profiler.h"

ProfileScope::ProfileScope(const std::string& name):
	m_name(name),
	m_startTime(std::chrono::high_resolution_clock::now())
{}

ProfileScope::~ProfileScope()
{
	// 終了時間の取得
	const auto endTime = std::chrono::high_resolution_clock::now();
	
	// 経過時間を取得
	const auto elapsed = endTime - m_startTime;

	// ミリ秒へ変換
	const float elapsedMilloSecond = std::chrono::duration<float, std::milli>(elapsed).count();

	// レコードの作成・設定
	Profiler::Record record;
	record.name = m_name;
	record.elapsedMilliSecond = elapsedMilloSecond;

	// Profilerに送る
	Profiler::AddRecord(record);
}
