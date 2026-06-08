#pragma once
namespace{
	// マップの範囲
	constexpr int MAP_SQUARE_WIDTH_COUNT = 33;
	constexpr int MAP_SQUARE_HEIGHT_COUNT = 33;
	// エリア分割回数
	const int _AREA_DEVIDE_COUNT = 8;
	// 最小部屋サイズ
	const int _MIN_ROOM_SIZE = 3;

	enum eTerrain {
		Invalid = -1,	// 無効な値
		Passage,		// 通路
		Room,			// 部屋
		Wall,			// 壁
	};
}