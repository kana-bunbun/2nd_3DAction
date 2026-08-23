#pragma once
#include"Input/InputConst.h"
#include<vector>
/// <summary>
/// アクション単位が保持する情報
/// </summary>
struct ActionKeyParam {
public:
	// アクションに対応したキー
	std::vector<Input::Key> keys;
};