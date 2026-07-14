#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>
#include"Vector3.h"
namespace Data {
	namespace Csv {
		// 肥大化を防ぐために型変換に関する処理を記載する

		template<typename T>
		T Convert(const std::string& str) {
			static_assert(sizeof(T) == 0, "Convert 定義されていない型");
			return T{};

		}

		// int型に型変換
		template<>
		inline int Convert<int>(const std::string& str) {
			return std::stoi(str);
		}
		// flaot型に型変換
		template<>
		inline float Convert<float>(const std::string& str) {
			return std::stof(str);
		}
		// double型に型変換
		template<>
		inline double Convert<double>(const std::string& str) {
			return std::stod(str);
		}
		// std::string型に型変換
		// 未定義の型を防ぐよう念のため記載
		template<>
		inline std::string Convert<std::string>(const std::string& str) {
			return str;
		}
		// bool型に型変換
		template<>
		inline bool Convert<bool>(const std::string& str) {
			if (str == "true" || str == "1")return true;
			if (str == "false" || str == "0")return false;

			assert(false && "comvert<bool> input error");

			return false;
		}
		/// <summary>
		/// Vector3 型に変換
		/// </summary>
		template<>
		inline Vector3 Convert<Vector3>(const std::string& str) {
			Vector3 vec = Vector3::zero;

			std::stringstream ss(str);
			char separate = ',';

			ss >> vec.x >> separate >> vec.y >> separate >> vec.z;
			return vec;

		}
	}
}
