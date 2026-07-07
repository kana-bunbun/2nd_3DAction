#pragma once
#include"../Utility/MyMath.h"

/// <summary>
/// FollowCameraクラスのパラメータ
/// 角度のパラメータはデグリー角で指定
/// </summary>
struct FollowCameraParam
{
public:
    float fieldOfView = 60.0f;       	// カメラの視野角 FOV = field of view

    float distanceToTarget = 600.0f; 	// カメラの被写体までの初期距離
    float minDistance = 350;         	// 被写体との最短距離
    float maxDistance = 850;         	// 被写体との最長距離
    float angleSpeed = 2.0f;         	// カメラの角速度

    float initCameraHeight = 150.0f;		// カメラの初期の高さ
    float lowAngle = -30.0f;				// カメラの最大仰角
    float highAngle = 80.0f;				// カメラの最大俯角
};