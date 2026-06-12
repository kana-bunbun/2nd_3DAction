#pragma once
#include"MapConst.h"
#include"DistanceNodeManhattanTable.h"
#include"DistanceNodeManhattan.h"
#include"ManhattanMoveData.h"
#include"MapTile.h"
#include<vector>
#include<functional>
class RouteSearcher
{
public:
	static RouteSearcher& GetInstance();


	std::vector<ManhattanMoveData>RouteSearchManhattan(int startID, int goalID, std::function<bool(MapTile)>tileCheck);

private:
	void OpenNodeToGoalManhattan(int startID, int goalID, std::function<bool(MapTile)>tileCheck);
	std::vector<ManhattanMoveData>CreateRouteManhattan();
	DistanceNodeManhattan* GetMinScoreNode(int goalX, int goalY);
	void OpenNodeAroundManhattan(DistanceNodeManhattan* baseNode, int goalId, std::function<bool(MapTile)>tileCheck);
private:

	// シングルトンなのでprivate
	RouteSearcher() = default;
	// コピー禁止
	RouteSearcher(const RouteSearcher&) = delete;
	// コピー代入禁止
	RouteSearcher& operator = (const RouteSearcher&) = delete;
	// ムーブ禁止
	RouteSearcher(RouteSearcher&&) = delete;
	// ムーブ代入禁止
	RouteSearcher& operator=(const RouteSearcher&&) = delete;
private:
	DistanceNodeManhattanTable* m_manhattanTable;
};

