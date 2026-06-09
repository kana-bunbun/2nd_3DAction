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
