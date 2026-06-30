#pragma once
#include"../Utility/Vector3.h"
#include<cassert>
namespace Camera{
	struct CameraView
	{
		Vector3 position;	// 座標
		Vector3 target;		// 注視点
		float fov;			// 視野角 field of view

		Vector3 GetForward() const
		{
			Vector3 dir;
			dir = position - target;
			// 0割り対策
			if (dir.IsLengthNearlyZero()) {
				assert(0 && "CameraView::GetForward");
				return Vector3::zero;
			}
			return dir.Normalize();
		}
		Vector3 GetPlaneVectorForward()const {
			Vector3 vec = GetForward();
			vec.y = 0.0f;
			// 0割り対策
			if (vec.IsLengthNearlyZero()) {
				assert(0 && "CameraView::GetForward");
				return Vector3::zero;
			}
			return vec.Normalize();

		}
		Vector3 GetPlaneVectorRight()const {
			Vector3 vec = GetPlaneVectorForward();
			vec.y = 0.0f;
			// 0割り対策
			if (vec.IsLengthNearlyZero()) {
				assert(0 && "CameraView::GetForward");
				return Vector3::zero;
			}
			return Vector3(vec.z, 0.0f, -vec.x);

		}
	};

	enum class CameraType {
		Follow,
		Debug,
		Max,
	};
}
class ICamera
{
public:
	virtual ~ICamera() = default;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(float deltaTime) = 0;
	/// <summary>
	/// 現在のカメラデータを取得
	/// </summary>
	/// <returns></returns>
	virtual Camera::CameraView GetView()const = 0;
	/// <summary>
	/// カメラシェイクをさせる関数
	/// </summary>
	/// <param name="power"></param>
	/// <param name="second"></param>
	virtual void TakeShake(float power, float second) {};
};

