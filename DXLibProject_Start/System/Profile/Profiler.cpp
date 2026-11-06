#include "Profiler.h"
#include "ProfileRecord.h"

namespace {
	/// <summary>
	/// 現在のフレームの計測結果
	/// </summary>
	std::vector<Profiler::Record> currentRecords;
}
void Profiler::BeginFrame()
{
	currentRecords.clear();
}

void Profiler::EndFrame(){}

void Profiler::AddRecord(const Record & record)
{
	currentRecords.emplace_back(record);
}

const std::vector<Profiler::Record>& Profiler::GetRecords()
{
	return currentRecords;
}
