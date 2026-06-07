#include "MapDraw.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"

#include<DxLib.h>
#include<vector>
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
		}
	}

}

bool MapDraw::InDevideList(size_t id)
{
	std::vector<int >devideLine = MapCreate::GetInstance().GetDevidLine();
	for (int i = 0; i < devideLine.size(); i++) {
		if (devideLine[i] == id)return true;
	}
	return false;
}
