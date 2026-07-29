#pragma once
#pragma once
#include<cassert>
#include"Data.h"
#include"JsonConvert.h"
#include"../Data/CameraParam.h"
#include"../Data/ModelPathParam.h"

namespace Data {
	namespace Json {
		// 肥大化を防ぐためにデータ変換に関する処理を記載する

		// デフォルトでは未定義で使ったらエラーになる
		template<typename T>
		struct FromJson {
			static T Binding(const Csv::Row& row) {
				static_assert(sizeof(T) == 0, "JSON Binding 定義されていない型");
				return T{};
			}
		};
		template<typename T>
		T Get(const JsonObject& json,std::string& key) {
			// データの中にKeyが存在しているかどうかチェック
			if (!json.contains(key)) {
				assert(false && "key not found");
			}

			// 見つけたらデータを取得
			const JsonObject& value = json.at(key);

			// 変換して返す
			return Convert<T>(value);

		};
		template<>
		struct FromJson<FollowCameraParam> {
			static FollowCameraParam Binding(const Csv::Row& row) {
				FollowCameraParam param;
				param.fieldOfView = Convert<float>(row.at("fieldOfView"));
				param.initDistance = Convert<float>(row.at("initDistance"));
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
		struct FromJson<ModelPathParam> {
			static ModelPathParam Binding(const Csv::Row& row) {
				ModelPathParam param;
				param.basePath = Convert<std::string>(row.at("basePath"));
				param.motionPath = param.motionPath + param.basePath + Convert<std::string>(row.at("motionPath"));
				param.modelPath = Convert<std::string>(row.at("modelPath"));
				int animNum= Convert<int>(row.at("animNum"));
				for (int i = 0; i < animNum; i++) {
					std::string header = "animPath[" + std::to_string(i) + "]";
					std::string animPath = param.motionPath + Convert<std::string>(row.at(header));
					param.animationPath.emplace_back(animPath);
				}
				return param;
			}
		};
	}
}

