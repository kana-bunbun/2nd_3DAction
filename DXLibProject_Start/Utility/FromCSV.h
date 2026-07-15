#pragma once
#include<cassert>
#include"Data.h"
#include"CsvConvert.h"
#include"../Camera/CameraParam.h"
#include"../World/Character/Player/PlayerModelParam.h"
#include"../World/Object/Item/BlendRecipe.h"
#include"Color.h"
namespace Data {
	namespace Csv {
		// 肥大化を防ぐためにデータ変換に関する処理を記載する

		// デフォルトでは未定義で使ったらエラーになる
		template<typename T>
		struct FromCsv {
			static T Binding(const Csv::Row& row) {
				static_assert(sizeof(T) == 0, "CsvBinding 定義されていない型");
				return T{};
			}
		};
		template<>
		struct FromCsv<FollowCameraParam> {
			static FollowCameraParam Binding(const Csv::Row& row) {
				FollowCameraParam param;
				param.fieldOfView = Convert<float>(row.at("fieldOfView"));
				param.initDistance= Convert<float>(row.at("initDistance"));
				param.minDistance = Convert<float>(row.at("minDistance"));
				param.maxDistance = Convert<float>(row.at("maxDistance"));
				param.minPitchDegAngle = Convert<float>(row.at("minPitchDegAngle"));
				param.maxPitchDegAngle = Convert<float>(row.at("maxPitchDegAngle"));
				param.moveSpeed = Convert<float>(row.at("moveSpeed"));
				param.rotateSpeedDeg = Convert<float>(row.at("rotateSpeedDeg"));
				param.offsetPos = Convert<Vector3>(row.at("offsetPos"));
				return param;
			}
		};
		template<>
		struct FromCsv<ModelPathParam> {
			static ModelPathParam Binding(const Csv::Row& row) {
				ModelPathParam param;
				param.basePath = Convert<std::string>(row.at("basePath"));
				param.motionPath= param.motionPath + param.basePath+Convert<std::string>(row.at("motionPath"));
				param.modelPath = param.basePath + Convert<std::string>(row.at("modelPath"));
				int animNum = Convert<int>(row.at("animNum"));
				for (int i = 0; i < animNum; i++) {
					std::string header = "animPath[" + std::to_string(i) + "]";
					std::string animPath = param.motionPath + Convert<std::string>(row.at(header));
					param.animationPath.emplace_back(animPath);
				}
				return param;
			}
		};
		template<>
		struct FromCsv<BlendRecipe> {
			static BlendRecipe Binding(const Csv::Row& row) {
				BlendRecipe param;
				for (int i = 0; i < static_cast<int>(ItemData::Type::Max); i++) {
					std::string itemName = BlendRecipe::ItemTypeToS(static_cast<ItemData::Type>(i));
					ItemData::Type blendResult = Convert<ItemData::Type>(row.at(itemName));
					param.blendRecipe[i] = blendResult;
				}
				return param;
			}
		};
		template<>
		struct FromCsv<Color_F> {
			static Color_F Binding(const Csv::Row& row) {
				Color_F param;
				param.red = Convert<float>(row.at("Red"));
				param.green = Convert<float>(row.at("Green"));
				param.blue = Convert<float>(row.at("Blue"));
				param.alpha = Convert<float>(row.at("Alpha"));
				return param;
			}
		};
	
	}
}

