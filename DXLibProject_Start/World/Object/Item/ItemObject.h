#pragma once
#include"../../GameObject.h"
class ItemObject:public GameObject
{
public:
	/// <summary>
	/// 使用時の初期化処理
	/// </summary>
	virtual void Setup(const Transform& transform){}
	/// <summary>
	/// 回転速度をランダムに求める
	/// </summary>
	virtual void RandomRotate();
protected:
	// 移動方向
	Vector3 m_moveVector;
	// 回転速度
	Vector3 m_rotateSpeed;
};

