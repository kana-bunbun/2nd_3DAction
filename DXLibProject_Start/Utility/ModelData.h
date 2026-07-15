#pragma once
#include<string>
#include"../World/Character/AnimationController.h"
struct ModelData {			// モデルのデータ
public:
	int modelHandle = -1;		// モデルハンドル
	std::string modelName;	// データの名前
	AnimationController anim;// アニメーション管理

};