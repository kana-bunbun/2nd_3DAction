#pragma once
/// <summary>
/// A*での経路探索処理
/// </summary>
class DistanceNode {

public:
    DistanceNode()=default;
    ~DistanceNode()=default;

    int GetTileID() { return m_tileID; }
    int GetDistance() { return m_distance; }
    // スコア取得処理
    virtual int GetScore(int goalx, int goalY) = 0;
protected:
    // 実コスト　スタートマスからどれだけ離れているか
    int m_distance;
    // マスのID
    int m_tileID;
};
