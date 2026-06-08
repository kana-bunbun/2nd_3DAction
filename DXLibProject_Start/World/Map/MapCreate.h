#pragma once
#include"../../Utility/Vector3.h"
#include"MapTile.h"
#include<vector>
/// <summary>
/// ランダムマップの生成
/// </summary>
class MapCreate
{
private:
	// マップ生成時に区切るエリアの情報
	class AreaData {
	public:
		// 始点
		int startX = -1;
		int startY = -1;
		int sizeX = -1;
		int sizeY = -1;
		AreaData()=default;
		AreaData(int startX,int startY, int sizeX,int sizeY) :startX(startX),startY(startY), sizeX(sizeX) ,sizeY(sizeY){}
	};
public:
	static MapCreate& GetInstance();
	/// <summary>
	/// マップ生成処理
	/// </summary>
	void CreateMap();
	/// <summary>
	/// 最初の大枠を作る
	/// </summary>
	void CreateFirstArea();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="tile"></param>
	void SetFirstWall(MapTile* tile);
	void AddDivideLine(MapTile* tile);
	void DivideAreaFixCount();
	void DivideArea(AreaData* divideArea, bool isVertical);
	void DivideAreaVertical(AreaData* divideArea);
	void DivideAreaHorizontal(AreaData* divideArea);
	AreaData* GetMaxSizeArea();

    void CreateAllRoom();
    void CreateRoom(AreaData* area);
	const std::vector<AreaData*>& GetAreaData() { return m_areaData; }

	// 分割線のマスのIDリスト
	const std::vector<int>& GetDivideLine(){ return m_divideLine; }

private:

	// シングルトンなのでprivate
	MapCreate() = default;
// コピー禁止
	MapCreate(const MapCreate&) = delete;
	// コピー代入禁止
	MapCreate& operator = (const MapCreate&) = delete;
	// ムーブ禁止
	MapCreate(MapCreate&&) = delete;
	// ムーブ代入禁止
	MapCreate& operator=(const MapCreate&&) = delete;
private:
	// エリアの配列
	std::vector<AreaData*> m_areaData;
	// 分割線のマスのIDリスト
	std::vector<int> m_divideLine;
	// エリアの分割回数
};

//private void CreateAllRoom()
//{
//    for (int i = 0; i < _areaList.Count; i++)
//    {
//        CreateRoom(_areaList[i]);
//    }
//}
//private void CreateRoom(AreaData area)
//{
//    if (area == null) return;
//
//    // 部屋のサイズ決定
//    int roomWidth = Random.Range(_MIN_ROOM_SIZE, area.width - 2 + 1);
//    int roomheight = Random.Range(_MIN_ROOM_SIZE, area.height - 2 + 1);
//    // 部屋の位置決定
//    int xRandomRange = area.width - roomWidth;
//    int yRandomRange = area.height - roomheight;
//    int startX = area.startX + Random.Range(1, xRandomRange);
//    int startY = area.startY + Random.Range(1, yRandomRange);
//    // 部屋の生成
//    List<int> roomidList = new List<int>(roomWidth * roomheight);
//    for (int y = 0; y < roomheight; y++)
//    {
//        for (int x = 0; x < roomWidth; x++)
//        {
//            SquareObject square = MapSquareManager.instance.GetSquare(startX + x, startY + y);
//            if (square == null) continue;
//            // マスを部屋地形に変更
//            square.SetTerrain(eTerrain.Room);
//            roomidList.Add(square.squareData.Id);
//        }
//    }
//    MapSquareManager.instance.AddRoom(roomidList);
//}

/// <summary>
/// すべての部屋をつなげる
/// </summary>
private void ConnecctAllRoom()
{
    // 掘削方向の決定
    eDerectionFour digDirection = (eDerectionFour)Random.Range(0, (int)eDerectionFour.Max);


    for (int i = 0; i < _areaList.Count - 1; i++)
    {
        // エリアから分割線まで掘る
        AreaData area1 = _areaList[i];



        // 次のエリアを分割線まで掘る
        AreaData area2 = _areaList[i + 1];

        // 分割線内で通路をつなげる

        // 掘削方向を決定


    }
}

/// <summary>
/// 指定エリアから指定方向に分割線まで掘る
/// </summary>
/// <param name="area"></param>
/// <param name="direction"></param>
private void DigToDevideLine(AreaData area, eDerectionFour direction)
{
    // 掘削開始マスを決定
    // 掘削方向の逆方向を取得
    eDerectionFour reverse = direction.ReverseDerection();
    // areaへのアクセスの回数を減らすためキャッシュ
    int startX = area.startX;
    int startY = area.startY;
    // エリアのすべてのマスから壁かつ、掘削方向と逆方向の隣接マスが部屋マスのマスを集約
    for (int y = 0; y < area.width; y++)
    {
        for (int x = 0; x < area.height; x++)
        {
            SquareObject square = MapSquareManager.instance.GetSquare(startX + x, startY + y);
            // 壁でなければ処理しない
            if (square == null || square.squareData.terrain != eTerrain.Wall) continue;
            // 掘削方向の逆のエリアを取得
        }

    }
    // ↑からランダムに1マス抽選

    // 分割線までの掘削
}
