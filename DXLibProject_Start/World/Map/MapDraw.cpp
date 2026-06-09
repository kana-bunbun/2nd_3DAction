#include "MapDraw.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"../../Utility/Game.h"
#include"../../Utility/Color.h"
#include<DxLib.h>
#include<vector>

namespace {
	constexpr Vector3 drawCenter = { Game::kScreenWidth- 180.0f,180.0f,0.0f };
	constexpr Vector3 drawSize = { 250.0f,250.0f,0.0f };
	constexpr Vector3 blockSize = { 5.0f,5.0f,0.0f };
	constexpr Vector3 blockInterval = { blockSize.x /*+ 2.0f*/,blockSize.y /*+ 2.0f*/,0.0f };
	constexpr Vector3 drawBlockStart ={
		-(blockInterval.x* (static_cast<float>(MAP_SQUARE_WIDTH_COUNT) * 0.5f) - (blockInterval.x * 0.5f) * (MAP_SQUARE_WIDTH_COUNT % 2)),
		blockInterval.y* (static_cast<float>(MAP_SQUARE_HEIGHT_COUNT) * 0.5f) - (blockInterval.y * 0.5f) * (MAP_SQUARE_WIDTH_COUNT % 2),
		0.0f};
	constexpr float sphereSize = 5;
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

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawBox(drawCenter.x - (drawSize.x * 0.5f), drawCenter.y - (drawSize.y * 0.5f),
	//	drawCenter.x + (drawSize.x * 0.5f), drawCenter.y + (drawSize.y * 0.5f),
	//	0x000000, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//Vector3 pos;

	//float sphereSize = 100;
	//for (int y = 0; y < MAP_SQUARE_HEIGHT_COUNT; y++) {
	//	for (int x = 0; x < MAP_SQUARE_WIDTH_COUNT; x++) {
	//		pos.x = x * sphereSize*2;
	//		pos.z = y * sphereSize*2;
	//		int color = 0xffffff;
	//		eTerrain terrain = MapManager::GetInstance().GetTile(MapManager::GetInstance().PositionToID(x, y))->GetSquareData()->GetTerrain();
	//		switch (terrain) {
	//		case::eTerrain::Invalid:
	//			break;
	//		case::eTerrain::Passage:
	//			color = Color::kCyan;
	//			break;
	//		case::eTerrain::Room:
	//			color = Color::kBlue;
	//			break;
	//		case::eTerrain::Wall:
	//			color = Color::kRed;
	//			break;
	//		default:
	//			color = 0xffffff;
	//			break;
	//		}
	//		if (InDevideList(MapManager::GetInstance().PositionToID(x, y))) {
	//			color = Color::kCyan;
	//		}
	//		//else {
	//		//}
	//		DrawSphere3D(pos.ToVECTOR(), sphereSize, 10, color, color, true);

	//		Vector3 drawBox = drawCenter + Vector3(-blockInterval.x * x, blockInterval.y * y, 0.0f) - drawBlockStart;
	//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//		DrawBox(drawBox.x - (blockSize.x * 0.5f), drawBox.y - (blockSize.y * 0.5f),
	//			drawBox.x + (blockSize.x * 0.5f), drawBox.y + (blockSize.y * 0.5f),
	//			color, TRUE);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	}
	//}

	DrawMap();
	DrawMiniMap();

}

void MapDraw::DrawMap()
{
	Vector3 pos;

	for (int y = 0; y < MAP_SQUARE_HEIGHT_COUNT; y++) {
		for (int x = 0; x < MAP_SQUARE_WIDTH_COUNT; x++) {
			pos.x = x * sphereSize * 2;
			pos.y = -sphereSize;
			pos.z = y * sphereSize * 2;
			int color = 0xffffff;
			eTerrain terrain = MapManager::GetInstance().GetTile(MapManager::GetInstance().PositionToID(x, y))->GetSquareData()->GetTerrain();
			switch (terrain) {
			case::eTerrain::Invalid:
				continue;
				break;
			case::eTerrain::Passage:
				color = Color::kCyan;
				break;
			case::eTerrain::Room:
				color = Color::kBlue;
				break;
			case::eTerrain::Wall:
				color = Color::kRed;
				break;
			default:
				color = 0xffffff;
				break;
			}
			if (InDevideList(MapManager::GetInstance().PositionToID(x, y))) {
				color = Color::kCyan;
			}
			DrawSphere3D(pos.ToVECTOR(), sphereSize, 10, color, color, true);

		}
	}
}

void MapDraw::DrawMiniMap()
{

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawBox(drawCenter.x - (drawSize.x * 0.5f), drawCenter.y - (drawSize.y * 0.5f),
	//drawCenter.x + (drawSize.x * 0.5f), drawCenter.y + (drawSize.y * 0.5f),
	//0x000000, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int y = 0; y < MAP_SQUARE_HEIGHT_COUNT; y++) {
		for (int x = 0; x < MAP_SQUARE_WIDTH_COUNT; x++) {
			int color = 0xffffff;
			eTerrain terrain = MapManager::GetInstance().GetTile(MapManager::GetInstance().PositionToID(x, y))->GetSquareData()->GetTerrain();
			switch (terrain) {
			case::eTerrain::Invalid:
				//continue;
				color = 0x000000;
				break;
			case::eTerrain::Passage:
				color = Color::kCyan;
				break;
			case::eTerrain::Room:
				color = Color::kBlue;
				break;
			case::eTerrain::Wall:
				color = Color::kRed;
				break;
			default:
				color = 0xffffff;
				break;
			}
	/*		if (InDevideList(MapManager::GetInstance().PositionToID(x, y))) {
				color = Color::kCyan;
			}*/

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
