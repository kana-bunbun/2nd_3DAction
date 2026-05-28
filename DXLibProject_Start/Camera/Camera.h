#pragma once
#include"../Utility/Vector3.h"
namespace Camera{
	struct CameraView
	{
		Vector3 position;	// 座標
		Vector3 target;		// 注視点
		float fov;			// 視野角 field of view
	};
}
class ICamera
{
public:
	virtual ~ICamera() = default;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 現在のカメラデータを取得
	/// </summary>
	/// <returns></returns>
	virtual Camera::CameraView GetView()const = 0;
	/// <summary>
	/// カメラの前方向ベクトルを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetForward()const = 0;
	/// <summary>
	/// Yawラジアン角を取得
	/// </summary>
	/// <returns></returns>
	virtual float GetYawRad()const = 0;

};

