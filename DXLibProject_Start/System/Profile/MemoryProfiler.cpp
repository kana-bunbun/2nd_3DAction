#include "MemoryProfiler.h"

#include<Windows.h>
#include<Psapi.h>

namespace {
    size_t currentMemory = 0;
    size_t peakMemory = 0;
}

void MemoryProfiler::Update()
{
    // 現在のプロセスを取得
    // GetCurrentProcess関数では実行中のプロセスが取得できる
    HANDLE process = GetCurrentProcess();

    // 計測結果受け取る変数を用意
    PROCESS_MEMORY_COUNTERS counters{};

    // Windowsへ実行中のプロセスで使用しているメモリ情報をcountersへ格納する
    if (GetProcessMemoryInfo(process, &counters, sizeof(counters))) {
        currentMemory = counters.WorkingSetSize;
        peakMemory = counters.PeakWorkingSetSize;
    }

}

size_t MemoryProfiler::GetCurrentMemory()
{
    return currentMemory;
}

size_t MemoryProfiler::GetPeakMemory()
{
    return peakMemory;
}

float MemoryProfiler::GetCyrrentMemoryMB()
{
    float memoryMB = GetCurrentMemory() / 1024.0f / 1024.0f;
    return memoryMB;
}

float MemoryProfiler::GetPeakMemoryMB()
{
    float peakMemoryMB = GetPeakMemory() / 1024.0f / 1024.0f;
    return peakMemoryMB;
}
