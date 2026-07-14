#pragma once
#include<string>
#include<cassert>

#include"Vector3.h"
#include"Data.h"

namespace Data{
	namespace Json {
		// 肥大化を防ぐために型変換に関する処理を記述する

		// jsonファイルはcsvとは異なり、読み込んだ中間データにプリミティブ型なら型情報を持っている
		// 意向で作成しているプリミティブ型のへんかんしょりは作らなくてもよいが
		// csvのデータ変換の考え方を踏襲し
		// 読み込んだデータをゲームで使用する方に変換する意識を持つために実装する

		//
		template<typename T>
		T Convert(const JsonObject& json) {
			static_assert(sizeof(T) == 0, "JSON Convert 定義されていない型");
			return T{};
		}

		// プリミティブ型へ返還
		// .getで対応

		// int型へ変換
		template<>
		inline int Convert<int>(const JsonObject& json) {
			// jsonデータにデータがあるかどうか確認
			assert(json.is_number());
			return json.get<int>();
		}
		// float型へ変換
		template<>
		inline float Convert<float>(const JsonObject& json) {
			// jsonデータにデータがあるかどうか確認
			assert(json.is_number());
			return json.get<float>();
		}
		// double型へ変換
		template<>
		inline double Convert<double>(const JsonObject& json) {
			// jsonデータにデータがあるかどうか確認
			assert(json.is_number());
			return json.get<double>();
		}
		// string型へ変換
		template<>
		inline std::string Convert<std::string>(const JsonObject& json) {
			// jsonデータにデータがあるかどうか確認
			assert(json.is_string());
			return json.get<std::string>();
		}
		// bool型へ変換
		template<>
		inline bool Convert<bool>(const JsonObject& json) {
			// jsonデータにデータがあるかどうか確認
			assert(json.is_boolean());
			return json.get<bool>();
		}
		// オリジナル型へ変換
		// 各メンバに手動で設定
		template<>
		inline Vector3 Convert<Vector3>(const JsonObject& json) {
			// jsonデータに各データが設定されているかどうか確認

			assert(json.contains("x"));
			assert(json.contains("y"));
			assert(json.contains("z"));
			Vector3 vec;
			vec.x = Convert<float>(json.at("x"));
			vec.y = Convert<float>(json.at("y"));
			vec.z = Convert<float>(json.at("z"));
			return vec;
		}

	}
}
