#include "CsvLoader.h"

#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>

#include<typeinfo>

namespace {
	const char* const kResourePath = "Resource\\CSV\\";
}

CsvLoader::CsvLoader(std::string filePath):
	m_loadData()
{
	std::string path = kResourePath;
	path += filePath;
	bool loaded = LoadCSVData(path);
	// 読み込みが失敗していたら警告
	if (!loaded) {
		assert(false && "CSVデータの読み込みに失敗しました");
	}
}

std::vector<std::string> CsvLoader::Split(const std::string & str, char separate)
{
	// 区切った値を格納する配列
	std::vector<std::string>spritData;

	// char版の文字列入出力ストリーム
	std::stringstream stream(str);

	// 区切った文字を格納する変数
	std::string buf;

	// 文字列を1文字ずつ区切る
	while (std::getline(stream, buf, separate)) {
		// 引数で指定した記号が見つかったら配列に追加
		spritData.push_back(buf);
	}
	// 区切った配列を返す
	return spritData;
}

bool CsvLoader::LoadCSVData(std::string filePath)
{
	// ファイルを開く
	std::ifstream ifs(filePath.c_str());

	// 読み込めない場合、処理をする前にfalseを返す
	if (!ifs.is_open())return false;
	
	// 1行の文字列を格納する変数
	std::string buf;

	// 配列の要素数を調べる
	while (std::getline(ifs, buf)) {
		
		// 1行何もなければスキップ
		if (buf.empty()) continue;
	
		// 行のサイズを1つ増やす
		m_loadData.resize(m_loadData.size() + 1);
		
		// 抜き出した1行をさらに1文字ずつ区切る
		auto split = Split(buf, ',');
		int size = split.size();

		// 1番最後の行の列のサイズを設定する
		m_loadData[m_loadData.size()-1].resize(size);
	}
	 ifs= std::ifstream(filePath.c_str());

	// 1行ずつ読み込み
	for (int y = 0; y < m_loadData.size(); y++) {
		
		// 1行に何も値がなければスキップ
		if (!std::getline(ifs, buf)) continue;
		
		// 1文字ずつ区切る
		auto split = Split(buf, ',');
		
		// 列の数だけ繰り返す
		for (int x = 0; x < split.size(); x++) {
		
			// 値を代入する
			m_loadData[y][x] = split[x];
		}
	}
	// ファイルを閉じる
	ifs.close();

	// 読み込みができたのでtrueを返す
	return true;
}
