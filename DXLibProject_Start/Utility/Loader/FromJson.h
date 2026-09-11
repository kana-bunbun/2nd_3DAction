#pragma once
#pragma once
#include<cassert>
#include"Data.h"
#include"JsonConvert.h"
#include"Data/CameraParam.h"
#include"Data/ModelPathParam.h"
#include"Stage/StageData.h"

namespace Data {
	namespace Json {
		// 肥大化を防ぐためにデータ変換に関する処理を記載する

		// デフォルトでは未定義で使ったらエラーになる
		template<typename T>
		struct FromJson {
			static T Binding(const JsonObject& row) {
				static_assert(sizeof(T) == 0, "JSON Binding 定義されていない型");
				return T{};
			}
		};
		template<typename T>
		T Get(const JsonObject& json,const std::string& key) {
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
			static FollowCameraParam Binding(const JsonObject& row) {
				FollowCameraParam param;
				param.fieldOfView = Get<float>(row,("fieldOfView"));
				param.initDistance = Get<float>(row,("initDistance"));
				param.minDistance = Get<float>(row,("minDistance"));
				param.maxDistance = Get<float>(row,("maxDistance"));
				param.minPitchDegAngle = Get<float>(row,("minPitchDegAngle"));
				param.maxPitchDegAngle = Get<float>(row,("maxPitchDegAngle"));
				param.moveSpeed = Get<float>(row,("moveSpeed"));
				param.rotateSpeedDeg = Get<float>(row,("rotateSpeedDeg"));
				param.offsetPos = Get<Vector3>(row,("offsetPos"));
				return param;
			}
		};
		template<>
		struct FromJson<ModelPathParam> {
			static ModelPathParam Binding(const JsonObject& json) {
				ModelPathParam param;
				param.basePath = Get<std::string>(json,("basePath"));
				param.motionPath = param.motionPath + param.basePath + Get<std::string>(json,("motionPath"));
				param.modelPath = Get<std::string>(json,("modelPath"));
				int animNum= Get<int>(json,("animNum"));
				for (int i = 0; i < animNum; i++) {
					std::string header = "animPath[" + std::to_string(i) + "]";
					std::string animPath = param.motionPath + Get<std::string>(json,(header));
					param.animationPath.emplace_back(animPath);
				}
				return param;
			}
		};
		template<>
		struct FromJson<Stage::ObjectData> {
			static Stage::ObjectData Binding(const JsonObject& json) {
				Stage::ObjectData data;
				data.partName = Get<std::string>(json, "partName");
				data.transform = Get<Transform>(json, "transform");
				return data;
			}
		};
	}
}

