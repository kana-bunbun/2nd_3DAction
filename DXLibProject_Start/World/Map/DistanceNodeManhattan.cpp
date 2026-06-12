#include "DistanceNodeManhattan.h"
#include "MapTile.h"
#include "MapManager.h"
#include "../../Utility/MyMath.h"

DistanceNodeManhattan::DistanceNodeManhattan(int distance, int tileID, MapConst::eDirectionFour direction, DistanceNodeManhattan* rootNode):
m_prevDirection(direction),
m_rootNode(rootNode)
{
	m_distance = distance;
	m_tileID = tileID;

}

int DistanceNodeManhattan::GetScore(int goalX, int goalY)
{
	MapTile* tile = MapManager::GetInstance().GetTile(m_tileID);
	// タイルが何も入っていなければint型の最大値を返す
	if (!tile || !tile->GetSquareData())return INT_MAX;

	int directionX = MyMath::Abs(goalX - tile->GetSquareData()->GetPosX());
	int directionY = MyMath::Abs(goalY - tile->GetSquareData()->GetPosY());

	return directionX + directionY + m_distance;
}
