#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>
#include"Vector3.h"
#include"Color.h"
#include"../Data/BlendRecipe.h"
#include"../World/GameObjectParam.h"
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
		/// <summary>
		/// ItemType型に型変換
		/// </summary>
		template<>
		inline ItemData::Type Convert<ItemData::Type>(const std::string& str) {
			return BlendRecipe::SToItemType(str);
		}
		/// <summary>
		/// COLOR_F 型に変換
		/// </summary>
		template<>
		inline Color_F Convert<Color_F >(const std::string& str) {
			Color_F color;

			std::stringstream ss(str);
			char separate = ',';

			ss >> color.red >> separate >> color.green >> separate >> color.blue >>separate >> color.alpha;
			return color;

		}
		/// <summary>
		/// CollisionTagに変換
		/// </summary>
		template<>
		inline CollisionTag Convert<CollisionTag >(const std::string& str) {
				
			if (str == "None")return CollisionTag::None;
			if (str == "Player")return CollisionTag::Player;
			if (str == "Dragon")return CollisionTag::Dragon;
			if (str == "Enemy")return CollisionTag::Enemy;
			if (str == "Wall")return CollisionTag::Wall;
			if (str == "Stage")return CollisionTag::Stage;
			if (str == "Barrier")return CollisionTag::Barrier;

			assert(0 && "Convert CollisionTag key not found");

			return CollisionTag::Invalid;
		}
		/// <summary>
		/// CollisionTypeに変換
		/// </summary>
		template<>
		inline CollisionType Convert<CollisionType>(const std::string& str) {
			if (str == "Normal")return CollisionType::Normal;
			if (str == "Body")return CollisionType::Body;
			if (str == "Foot")return CollisionType::Foot;
			if (str == "Sensor")return CollisionType::Sensor;
			if (str == "Attack")return CollisionType::Attack;
			if (str == "Heal")return CollisionType::Heal;
			if (str == "Null")return CollisionType::Null;
			assert(0 && "Convert CollisionType key not found");
			return CollisionType::Invalid;
		}
	}

}
