#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>
#include"../Vector3.h"
#include"../Color.h"
#include"Data/BlendRecipe.h"
#include"World/GameObjectParam.h"
#include"World/GameObject.h"
#include"World/Component/Collision.h"
#include"Utility/Color.h"
#include"Input/InputConst.h"
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
	
		/// <summary>
		/// ColorDataに変換
		/// プログラム上ではint型で扱っている
		/// intで型変換をしようとすると整数int型変数への影響が出る
		/// それを防ぐため専用の構造体を用いて変換する
		/// </summary>
		template<>
		inline Color::ColorData Convert<Color::ColorData>(const std::string& str) {
			if (str == "White")return { Color::kWhite };
			if (str == "Black")return { Color::kBlack };
			if (str == "Gray")return { Color::kGray };
			if (str == "Red")return { Color::kRed };
			if (str == "Green")return { Color::kGreen };
			if (str == "Blue")return { Color::kBlue };
			if (str == "Yellow")return { Color::kYellow };
			if (str == "Cyan")return { Color::kCyan };
			if (str == "Magenta")return { Color::kMagenta };
			assert(0 && "Convert CollisionType key not found");
			return { Color::kWhite };
		}
		template<>
		inline Input::Key Convert<Input::Key>(const std::string& str) {
			return static_cast<Input::Key>(stoi(str));
		}
		template<>
		inline Input::Device Convert<Input::Device>(const std::string& str) {
			return static_cast<Input::Device>(stoi(str));

		}
	
	}

}
