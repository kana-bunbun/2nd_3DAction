#pragma once

#include<memory>
#include<vector>
#include"../Utility/Vector3.h"
#include"../Camera/Camera.h"

/// <summary>
/// カメラを制御するクラス
/// カメラクラスのパラメータを受け取ってDXライブラリの描画処理を呼ぶ
/// </summary>
class CameraManager
{
public:
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
	//void SetActiveCamera(std::unique_ptr<ICamera> camera);

	/// <summary>
	/// 管理するカメラの追加
	/// </summary>
	/// <param name="camera"></param>
	void AddCamera(std::unique_ptr<ICamera> camera);

	/// <summary>
	/// 使用するカメラの設定
	/// </summary>
	/// <param name="activeIndex"></param>
	void SetActiveCamera(size_t activeIndex);

	/// <summary>
	/// カメラを切り替える
	/// </summary>
	void NextCamera();

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
	/// 保持しているカメラ群
	/// </summary>
	std::vector <std::unique_ptr<ICamera>> m_cameras;

	/// <summary>
	/// カメラの情報
	/// </summary>
	Camera::CameraView m_currentView;

	/// <summary>
	/// 現在使用しているカメラのインデックス
	/// </summary>
	size_t m_activeIndex;


};

