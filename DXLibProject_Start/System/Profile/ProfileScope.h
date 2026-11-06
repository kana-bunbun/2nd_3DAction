#pragma once
#include<chrono>
#include<string>
class ProfileScope
{
public:
	ProfileScope(const std::string& name);
	~ProfileScope();
private:

	/// <summary>
	/// 観測対象名
	/// </summary>
	std::string m_name;

	/// <summary>
	/// 計測開始時間
	/// </summary>
	std::chrono::high_resolution_clock::time_point m_startTime;

};