#pragma once

#include<memory>
#include"../Utility/Vector3.h"
#include"../Camera/Camera.h"

/// <summary>
/// カメラを制御するクラス
/// カメラクラスのパラメータを受け取ってDXライブラリの描画処理を呼ぶ
/// </summary>
class CameraManager
{
	CameraManager();
	~CameraManager();

	void Init();
	void Update();

	/// <summary>
	/// DXライブラリの描画に必要のパラメータを設定
	/// 描画システムに反映
	/// </summary>
	void Apply();
	/// <summary>
	/// カメラの設定
	/// </summary>
	/// <param name="camera"></param>
	void SetActiveCamera(std::unique_ptr<ICamera> camera);

	/// <summary>
	/// カメラの前方ベクトルの取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetForward()const;
	/// <summary>
	/// カメラのyawラジアンの取得
	/// </summary>
	/// <returns></returns>
	float GetYawRad()const;

private:
	/// <summary>
	/// 現在適応しているカメラ
	/// </summary>
	std::unique_ptr<ICamera>m_activeCamera;
	/// <summary>
	/// カメラの情報
	/// </summary>
	Camera::CameraView m_currentView;
};

