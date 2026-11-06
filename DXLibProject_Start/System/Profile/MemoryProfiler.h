#pragma once

namespace MemoryProfiler {

	void Update();

	/// <summary>
	/// 現在使用中のメモリを取得(Byte)
	/// </summary>
	size_t GetCurrentMemory();

	/// <summary>
	/// ピークメモリを取得(Byte)
	/// </summary>
	/// <returns></returns>
	size_t GetPeakMemory();

	/// <summary>
	/// 現在使用中のメモリを取得(MByte)
	/// </summary>
	/// <returns></returns>
	float GetCyrrentMemoryMB();

	/// <summary>
	/// ピークメモリを取得(MByte)
	/// </summary>
	/// <returns></returns>
	float GetPeakMemoryMB();

}