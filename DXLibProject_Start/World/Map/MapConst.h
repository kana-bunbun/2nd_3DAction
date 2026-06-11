#pragma once
namespace MapConst{
	// マップの範囲
	constexpr int MAP_SQUARE_WIDTH_COUNT = 32;
	constexpr int MAP_SQUARE_HEIGHT_COUNT = 32;
	// エリア分割回数
	const int AREA_DIVIDE_MAX = 13;
	const int AREA_DIVIDE_MIN = 2;
	// 最小部屋サイズ
	const int _MIN_ROOM_SIZE = 3;

	enum class eTerrain {
		Invalid = -1,	// 無効な値
		Passage,		// 通路
		Room,			// 部屋
		Wall,			// 壁
	};
	enum class eDirectionFour {
		Invalid = -1,	// 無効な値
		Up,
		Right,
		Down,
		Left,
		Max

	};
}