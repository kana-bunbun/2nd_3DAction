#pragma once
#include"../../GameObject.h"
class ItemObject:public GameObject
{
public:
	/// <summary>
	/// 使用時の初期化処理
	/// </summary>
	virtual void Setup(const Transform& transform){}
};

