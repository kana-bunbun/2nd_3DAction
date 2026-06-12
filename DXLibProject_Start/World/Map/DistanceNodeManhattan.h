#pragma once
#include"DistanceNode.h"
#include"MapConst.h"
/// <summary>
/// 四方向での経路探索
/// </summary>
class DistanceNodeManhattan :public DistanceNode {
public:
    DistanceNodeManhattan(int distance, int tileID, MapConst::eDirectionFour direction, DistanceNodeManhattan* rootNode);
    ~DistanceNodeManhattan() = default;
    int GetScore(int goalX, int goalY)override;
    DistanceNodeManhattan* GetRootNode() { return m_rootNode; }
    MapConst::eDirectionFour GetPrevDirection() { return m_prevDirection; }
private:
    // 親ノードからの移動方向
    MapConst::eDirectionFour m_prevDirection;
    // 親ノード
    DistanceNodeManhattan* m_rootNode;
};
