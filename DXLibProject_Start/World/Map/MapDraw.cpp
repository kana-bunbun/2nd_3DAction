#include "MapDraw.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"../../Utility/Game.h"
#include<DxLib.h>
#include<vector>

namespace {
	constexpr Vector3 drawCenter = { Game::kScreenWidth- 180.0f,180.0f,0.0f };
	constexpr Vector3 drawSize = { 250.0f,250.0f,0.0f };
	constexpr Vector3 blockSize = { 5.0f,5.0f,0.0f };
	constexpr Vector3 blockInterval = { blockSize.x + 2.0f,blockSize.y + 2.0f,0.0f };
	constexpr Vector3 drawBlockStart ={
		-(blockInterval.x* (static_cast<float>(MAP_SQUARE_WIDTH_COUNT) * 0.5f) - (blockInterval.x * 0.5f) * (MAP_SQUARE_WIDTH_COUNT % 2)),
		blockInterval.y* (static_cast<float>(MAP_SQUARE_HEIGHT_COUNT) * 0.5f) - (blockInterval.y * 0.5f) * (MAP_SQUARE_WIDTH_COUNT % 2),
		0.0f};

}

MapDraw::MapDraw()
{
	MapManager::GetInstance().Initialize();
	MapCreate::GetInstance().CreateMap();
}

MapDraw::~MapDraw()
{}

void MapDraw::Draw()
{
	Vector3 pos;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(drawCenter.x - (drawSize.x * 0.5f), drawCenter.y - (drawSize.y * 0.5f),
		drawCenter.x + (drawSize.x * 0.5f), drawCenter.y + (drawSize.y * 0.5f),
		0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int y = 0; y < MAP_SQUARE_HEIGHT_COUNT; y++) {
		for (int x = 0; x < MAP_SQUARE_WIDTH_COUNT; x++) {
			pos.x = x * 10;
			pos.z = y * 10;
			int color;
			if (InDevideList(MapManager::GetInstance().PositionToID(Vector3(x, y, 0.0f)))) {
				color = 0x00ff00;
			}
			else {
				color = 0xff0000;
			}
			DrawSphere3D(pos.ToVECTOR(), 5, 10, color, color, true);

			Vector3 drawBox = drawCenter + Vector3(-blockInterval.x * x, blockInterval.y * y, 0.0f) - drawBlockStart;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(drawBox.x - (blockSize.x * 0.5f), drawBox.y - (blockSize.y * 0.5f),
				drawBox.x + (blockSize.x * 0.5f), drawBox.y + (blockSize.y * 0.5f),
				color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
	}

}

bool MapDraw::InDevideList(size_t id)
{
	std::vector<int >devideLine = MapCreate::GetInstance().GetDivideLine();
	for (int i = 0; i < devideLine.size(); i++) {
		if (devideLine[i] == id)return true;
	}
	return false;
}
