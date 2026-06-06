#pragma once
namespace{
	constexpr int MAP_SQUARE_WIDTH_COUNT = 32;
	constexpr int MAP_SQUARE_HEIGHT_COUNT = 32;
	enum eTerrain {
		Invalid = -1,	// 無効な値
		Passage,		// 通路
		Room,			// 部屋
		Wall,			// 壁
	};
}