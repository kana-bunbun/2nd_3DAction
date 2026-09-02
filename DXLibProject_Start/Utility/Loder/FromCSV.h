#pragma once
#include<cassert>
#include<string>
#include<type_traits>
#include"Data.h"
#include"CsvConvert.h"
#include"Data/CameraParam.h"
#include"Data/ModelPathParam.h"
#include"Data/BlendRecipe.h"
#include"Data/ActionEffectParam.h"
#include"Data/ActionIntervalParam.h"
#include"../Color.h"
#include"World/Component/Collision.h"
#include"World/GameObjectParam.h"
#include"Data/UITextParam.h"
#include"Data/ActionParam.h"
#include"Data/GraphPathParam.h"
#include"Data/EffectPathParam.h"
#include"Input/InputConst.h"
#include"Data/InputKeyParam.h"
#include"Data/ActionKeyParam.h"

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
	/*	template<class T>
		struct FromCsv {
			static T Binding(const Csv::Row& row) {
				static_assert(sizeof(T) == 0, "CsvBinding 定義されていない型");
				return T{};
			}
		};*/
		template<typename T>
		T Get(const Csv::Row& row,  const std::string key) {
			// keyの値をrowから探す
			// 見つかればrowのvalueを、見つからなければend()が入る
			auto it = row.find(key);
			if (it == row.end()) {
				// 設定ミス
				assert(0 && "key not found");
				return T{};
			}
			// 見つかったらvalueを変換して返す
			return Convert<T>(it->second);
		}
		template<>
		struct FromCsv<FollowCameraParam> {
			static FollowCameraParam Binding(const Csv::Row& row) {
				FollowCameraParam param;
				param.fieldOfView = Get<float>(row,"fieldOfView");
				param.initDistance= Get<float>(row,"initDistance");
				param.minDistance = Get<float>(row,"minDistance");
				param.maxDistance = Get<float>(row,"maxDistance");
				param.minPitchDegAngle = Get<float>(row,"minPitchDegAngle");
				param.maxPitchDegAngle = Get<float>(row,"maxPitchDegAngle");
				param.moveSpeed = Get<float>(row,"moveSpeed");
				param.rotateSpeedDeg = Get<float>(row,"rotateSpeedDeg");
				param.offsetPos = Get<Vector3>(row,"offsetPos");
				return param;
			}
		};
		template<>
		struct FromCsv<ModelPathParam> {
			static ModelPathParam Binding(const Csv::Row& row) {
				ModelPathParam param;
				param.basePath = Get<std::string>(row,"basePath");
				param.motionPath= param.motionPath + param.basePath+Get<std::string>(row,"motionPath");
				param.modelPath = param.basePath + Get<std::string>(row,"modelPath");
				int animNum = Get<int>(row,"animNum");
				for (int i = 0; i < animNum; i++) {
					std::string header = "animPath[" + std::to_string(i) + "]";
					std::string animPath = param.motionPath + Get<std::string>(row,(header));
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
					ItemData::Type blendResult = Get<ItemData::Type>(row,(itemName));
					param.blendRecipe[i] = blendResult;
				}
				return param;
			}
		};
		template<>
		struct FromCsv<Color_F> {
			static Color_F Binding(const Csv::Row& row) {
				Color_F param;
				param.red = Get<float>(row,"red");
				param.green = Get<float>(row,"green");
				param.blue = Get<float>(row,"blue");
				param.alpha = Get<float>(row,"alpha");
				return param;
			}
		};
		template<>
		struct FromCsv<CollisionParam> {
			static CollisionParam Binding(const Csv::Row& row) {
				CollisionParam param;
				param.ID = Get<int>(row, "ID");
				param.shapeType= static_cast<CollisionShape>(Get<int>(row, "RangeType"));
				switch (param.shapeType) {
				case CollisionShape::Sphere:
					Sphere(param, row);
					break;
				case CollisionShape::AABB:
					AABB(param, row);
					break;
				}

				return param;
			}
			static void Sphere(CollisionParam& param,const Csv::Row& row) {
				param.radius = Get<float>(row, "Param[0]");
				param.position = Get<Vector3>(row, "Param[1]");
			}
			static void AABB(CollisionParam& param,const Csv::Row& row) {
				param.size = Get<Vector3>(row, "Param[0]");
				param.position = Get<Vector3>(row, "Param[1]");
			}
		};
		template<>
		struct FromCsv<ActionEffectParam> {
			static ActionEffectParam Binding(const Csv::Row& row) {
				ActionEffectParam param;
				param.ID = Get<int>(row, "ID");
				param.power = Get<int>(row, "power");
				return param;
			}
		};
		template<>
		struct FromCsv<ActionIntervalParam> {
			static ActionIntervalParam Binding(const Csv::Row& row) {
				ActionIntervalParam param;
				param.ID = Get<int>(row, "ID");
				param.maxSecond = Get<float>(row, "maxSecond");
				param.intervalSecond = Get<float>(row, "intervalSecond");
				param.firstInterval = Get<float>(row, "firstInterval");
				return param;
			}
		};
		template<>
		struct FromCsv<UITextParam> {
			static UITextParam Binding(const Csv::Row& row) {
				UITextParam param;
				param.normalColor = Get<Color::ColorData>(row, "normalColor").value;
				param.selectedColor = Get<Color::ColorData>(row, "selectedColor").value;
				param.fontName= Get<std::string> (row, "fontName");
				param.fontSize = Get<int>(row, "fontSize");
				param.thickness = Get<int>(row, "thickness");
				return param;
			}
		};
		template<>
		struct FromCsv<ActionParam> {
			static ActionParam Binding(const Csv::Row& row) {
				ActionParam param;
				param.ID = Get<int>(row, "ID");
				param.collisionID = Get<int>(row, "collisionID");
				param.effectID = Get<int>(row, "effectParamID");
				param.intervalID = Get<int>(row, "intervalID");
				return param;
			}
		};
		template<>
		struct FromCsv<GraphPathParam> {
			static GraphPathParam Binding(const Csv::Row& row) {
				GraphPathParam param;
				param.ID = Get<int>(row, "ID");
				param.graphName= Get<std::string>(row, "graphName");
				return param;
			}
		};
		template<>
		struct FromCsv<EffectPathParam> {
			static EffectPathParam Binding(const Csv::Row& row) {
				EffectPathParam param;
				param.ID = Get<int>(row, "ID");
				param.effectName= Get<std::string>(row, "effectName");
				return param;
			}
		};
		template<>
		struct FromCsv<InputKeyParam> {
			static InputKeyParam Binding(const Csv::Row& row) {
				InputKeyParam param;
				const int kActionKeyMax = 6;
				param.device = Get<Input::Device>(row, "DeviceID");
				param.ID = Get<int>(row, "KeyID");
				param.keyID = Get<int>(row, "DeviceKeyID");
				return param;
			}
		};
		template<>
		struct FromCsv<ActionKeyParam> {
			static ActionKeyParam Binding(const Csv::Row& row) {
				ActionKeyParam param;
				
				for (int i = 0; i < Input::kActionKeyMax; i++) {
					std::string keyID = "KeyID[" + std::to_string(i) + "]";
					Input::Key key = Get<Input::Key>(row, keyID);
					if (key == Input::Key::Invalid)continue;
					param.keys.push_back(key);
				}
				return param;
			}
		};
	}
}

