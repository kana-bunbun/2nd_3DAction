#pragma once
#include"pch.h"

#include"Data.h"
#include"FromCsv.h"

namespace Data{
	namespace Csv{
		template<typename T>
		std::vector<T>LoadCsvAs(const std::string& path) {
			// csvデータ読み込み
			Csv::Table table = Csv::LoadRawCSV(path);

			// データが空かどうかチェック
			if (table.empty()) {
				assert(false && "LoadCsvAs csv is Empty");
				return{};
			}
			// データがヘッダのみかどうかチェック
			if (table.size() < 2) {
				assert(false && "LoadCsvAs csv has no Data");
				return{};
			}

			// 行データへ変換
			const auto& rows = Csv::ToRows(table);
			// 変換結果を返す変数を用意
			// 読み込む量がわかっているのできちんとメモリを確保
			std::vector<T>result;
			result.reserve(rows.size());

			// 構造体へデータを格納
			for (const auto& row : rows) {
				result.push_back(FromCsv<T>::Binding(row));
			}
			return result;
		}

		
	}
}