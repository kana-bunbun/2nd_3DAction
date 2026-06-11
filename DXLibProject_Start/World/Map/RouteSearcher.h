#pragma once
class RouteSearcher
{
public:
	static RouteSearcher& GetInstance();

private:

    //// A*経路探索
    //class DistanceNode
    //{
    //    // 実コスト　スタートから何マス離れているか

    //    public int distance{ get; private set; } = -1;
    //    // マスID
    //    public int squareID{ get; private set; } = -1;
    //    public DistanceNode(int distance, int squareID)
    //    {
    //        this.distance = distance;
    //        this.squareID = squareID;
    //    }
    //    // スコア取得処理
    //    public abstract int GetScore(int goalX, int goalY);
    //}

    class DistanceNode {

    public:
        DistanceNode(int distance, int squareID);

        int GetSquareID() { return m_squareID; }
        int GetDistance() { return m_squareID; }
        virtual int GetScore(int goalx, int goalY) = 0;
    private:
        // 実コスト　スタートマスからどれだけ離れているか
        int m_distance;
        // マスのID
        int m_squareID;
    };

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

};

