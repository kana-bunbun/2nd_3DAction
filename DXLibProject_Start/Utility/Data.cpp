#include "Data.h"

#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>

Data::Csv::Table Data::Csv::LoadRawCSV(const std::string& path)
{
	// 結果を返す関数を用意
	Data::Csv::Table table;

	// ファイルを開く
	std::ifstream ifs(path);

	// ファイルを開けなかったら即時return
	if (ifs.fail()) {
		assert(false, "Data::Csv::LoadCSV Fail To Open CSV File");
		return table;
	}

	// 読み込んだデータを格納する変数を用意
	std::string line;

	while (std::getline(ifs, line))
	{
		// 1行を分割して格納
		table.push_back(Split(line));
	}

	return table;
}

std::vector<std::string> Data::Csv::Split(const std::string& str, char separate)
{
	// 結果を返す配列を用意
	std::vector<std::string> separateList;

	std::stringstream ss(str);

	// 分割したデータの一時保管する変数を宣言、最後の文字まで繰り返す
	std::string buf;

	// 文字列を1文字ずつ区切る
	while (std::getline(ss,buf,separate))
	{
		// 引数で指定した記号が見つかったら配列に追加
		separateList.push_back(buf);
	}
	// 区切った配列を返す
	return separateList;
}

std::vector <std::vector<int>> Data::Csv::TiIntTable(const Table& table)
{
	std::vector <std::vector<int>>intTable;
	for (const auto& line : table) {
		std::vector<int>row;
		for (const auto& cell : line) {
			row.push_back(std::stoi(cell));
		}
		intTable.push_back(row);
	}
	return intTable;
}
