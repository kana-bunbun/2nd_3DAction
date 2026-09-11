#pragma once
#include"pch.h"
#include"StageData.h"

/// <summary>
/// StageDataを作成、用意するクラス
/// </summary>
class StageBuilder
{
public:
	// StageDataを返す関数
	// ゲーム中に出てくるステージの数だけ用意

	Stage::StageData BuildStageTest()const;

	Stage::StageData BuildFromJson(const std::string& path) const;

};

