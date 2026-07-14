#pragma once
#include<string>
#include<cassert>

#include"Data.h"
#include"FromJson.h"

namespace Data {
	namespace Json {
		template<typename T>
		std::vector<T>LoadJsonAs(const std::string& path) {
			// Jsonデータの読み込み
			JsonObject json = LoadRawJSON(path);

			// データが空かどうかチェック
			if (json.empty())
			{
				assert(false && "LoasJsonAs json is empty");
				return {};
			}

			// 変換結果を返す変数を用意
			// 読み込む量がわかっているのできちんとメモリを確保
			std::vector<T>result;
			result.reserve(json.size());
			// 構造体へデータを格納
			for (const auto& obj : json) {
				result.emplace_back(FromJson<T>::Binding(obj));
			}

			return result;
		}
	}
}

