#include "RouteSearcher.h"
#include"MapConst.h"
#include"MapTile.h"
#include"MapManager.h"
RouteSearcher& RouteSearcher::GetInstance()
{
	static RouteSearcher instance;
	return instance;
}

std::vector<ManhattanMoveData> RouteSearcher::RouteSearchManhattan(int startID, int goalID, std::function<bool(MapTile)> tileCheck)
{
	// ゴールノードにたどり着くまでノードをオープン
	OpenNodeToGoalManhattan(startID, goalID, tileCheck);
	// 親ノードをたどってゴールノードからスタートノードまで経路を生成

	return CreateRouteManhattan();
}

void RouteSearcher::OpenNodeToGoalManhattan(int startID, int goalID, std::function<bool(MapTile)> tileCheck)
{
	m_manhattanTable->Crear();
	// スタートノードを生成
	m_manhattanTable->openList.push_back(new DistanceNodeManhattan(0, startID, MapConst::eDirectionFour::Invalid, nullptr));

	// ゴールマスを取得
	MapTile* goalTile = MapManager::GetInstance().GetTile(goalID);

	if (!goalTile || !goalTile->GetSquareData())return;
	// ゴール座標のキャッシュ
	int goalX = goalTile->GetSquareData()->GetPosX();
	int goalY = goalTile->GetSquareData()->GetPosY();
	// ゴールが無くなったらnullではなくなるためwhileを抜けられる
	while (!m_manhattanTable->goalNode) {
		// スコアの最小ノードを探す
		DistanceNodeManhattan* minScoreNode = GetMinScoreNode(goalX, goalY);
		// 最小ノードが見つからなければ終わる
		if (!minScoreNode)break;

		// 周りをオープン
		OpenNodeAroundManhattan(minScoreNode, goalID, tileCheck);
		// クローズする
		m_manhattanTable->openList.Remove(minScoreNode);	// オープン済みリストから取り除く
		m_manhattanTable->closeList.push_back(minScoreNode);
	}

}

std::vector<ManhattanMoveData> RouteSearcher::CreateRouteManhattan()
{
	std::vector<ManhattanMoveData> route;
	// ゴールにたどり着く道筋があるかどうかを判定
	if (!m_manhattanTable || !m_manhattanTable->goalNode)return route;
	// 道筋の回数をキャッシュ
	int routeNum = m_manhattanTable->goalNode->GetDistance();

	DistanceNodeManhattan* currentNode = m_manhattanTable->goalNode;
	for (int i = routeNum; i >= 0; i++) {
		ManhattanMoveData moveData = ManhattanMoveData(currentNode->GetRootNode()->GetTileID(), currentNode->GetTileID(), currentNode->GetPrevDirection());
		route[i] = moveData;
		// 親ノードを現在のノードにする
		currentNode = currentNode->GetRootNode();
	}
	return route;
}

DistanceNodeManhattan* RouteSearcher::GetMinScoreNode(int goalX, int goalY)
{
	if (m_manhattanTable->openList.size() < 1)return nullptr;

	int minScore = -1;
	DistanceNodeManhattan* result = nullptr;
	std::vector<DistanceNodeManhattan*>openList = m_manhattanTable->openList;

	for (int i = 0; i < openList.size(); i++) {
		DistanceNodeManhattan* node = openList[i];
		if (!node)continue;
		int nodeScore = node->GetScore(goalX, goalY);
		// 現在の最少スコア以上ならスキップ
		if (result && minScore <= nodeScore)continue;

		// 最少のスコアとノードを更新
		result = node;
		minScore = nodeScore;
	}
	return result;

	return nullptr;
}

void RouteSearcher::OpenNodeAroundManhattan(DistanceNodeManhattan* baseNode, int goalId, std::function<bool(MapTile)> tileCheck)
{
	if (!baseNode)return;
	// オープンするノードの実コストを決定
	int distance = baseNode->GetDistance() + 1;

	MapTile* tile = MapManager::GetInstance().GetTile(baseNode->GetTileID());

	int baseX = tile->GetSquareData()->GetPosX();
	int baseY = tile->GetSquareData()->GetPosY();
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);

		MapTile* openTile = MapManager::GetInstance().GetToDirSquare(baseX, baseY, direction);
		if (!openTile)continue;
		// すでにクローズ済みのマスなら処理しない
		if (std::find(m_manhattanTable->closeList.begin(), m_manhattanTable->closeList.end(), openTile->GetSquareData()->GetID()) != m_manhattanTable->closeList.end());
		// すでにオープン済みのマスなら処理しない
		if (std::find(m_manhattanTable->openList.begin(), m_manhattanTable->openList.end(), openTile->GetSquareData()->GetID()) != m_manhattanTable->openList.end());
		// 通行不可のマスなら処理しない
		if (tileCheck(openTile->GetSquareData()))continue;
	}
}
