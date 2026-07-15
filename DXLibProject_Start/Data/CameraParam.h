#pragma once
#include"../Utility/MyMath.h"

/// <summary>
/// FollowCameraクラスのパラメータ
/// 角度のパラメータはデグリー角で指定
/// </summary>
struct FollowCameraParam
{
public:
    float fieldOfView = 60.0f;       	    // カメラの視野角 FOV = field of view

    float initDistance = 600.0f;         	// カメラの被写体までの初期距離
    float minDistance = 350;         	    // 被写体との最短距離
    float maxDistance = 850;             	// 被写体との最長距離
    float minPitchDegAngle = -30.0f;		// カメラの最大仰角
    float maxPitchDegAngle = 80.0f;			// カメラの最大俯角

    float moveSpeed = 2.0f;            	    // カメラの角速度
    float rotateSpeedDeg = 2.0f;             	// カメラの角速度
    Vector3 offsetPos = { 0.0f,0.0f,0.0f }; // カメラのオフセット
    //float InitCameraHeight = 150.0f;		// カメラの初期の高さ
};