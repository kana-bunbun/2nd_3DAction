#pragma once
#include<vector>
#include<string>
#include"Vector3.h"
/// <summary>
/// ファイル名を指定しCSVのデータを読み込む
/// </summary>
class CsvLoader
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CsvLoader() = default;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="filePath">読み込みたいファイルパス</param>
	CsvLoader(std::string filePath);
	~CsvLoader() = default;
	/// <summary>
	/// 行の文字列を1文字ずつ区切る
	/// </summary>
	/// <param name="str">区切りたい文字列</param>
	/// <param name="separate">分割する記号</param>
	/// <returns></returns>
	std::vector<std::string>Split(const std::string& str, char separate);
	/// <summary>
	/// CSVデータを読み込む関数
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	bool LoadCSVData(std::string filePath);
	/// <summary>
	/// 読み込んだCSVデータを取得する関数
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<std::string>> GetLoadData() { return m_loadData; }

private:
	std::vector<std::vector<std::string>> m_loadData;
};

