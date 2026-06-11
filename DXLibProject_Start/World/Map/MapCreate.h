#pragma once
#include"../../Utility/Vector3.h"
#include"MapTile.h"
#include"MapConst.h"
#include<vector>
#include<memory>
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
	/// 全マスを壁で初期化
	/// </summary>
	void SetFirstWall(MapTile* tile);
	/// <summary>
	/// 分割線を追加
	/// </summary>
	void AddDivideLine(MapTile* tile);
	/// <summary>
	/// エリアを指定回数だけ分割
	/// </summary>
	void DivideAreaFixCount();
	/// <summary>
	/// 指定のエリアを分割
	/// </summary>
	void DivideArea(AreaData* divideArea, bool isVertical);
	/// <summary>
	/// 指定のエリアを上下に分割
	/// </summary>
	void DivideAreaVertical(AreaData* divideArea);
	/// <summary>
	/// 指定のエリアを左右に分割
	/// </summary>
	/// <param name="divideArea"></param>
	void DivideAreaHorizontal(AreaData* divideArea);
	/// <summary>
	/// 全エリアの中で縦か横のサイズが最大のエリアを取得
	/// </summary>
	/// <returns></returns>
	AreaData* GetMaxSizeArea();
    /// <summary>
    /// すべてのエリアの中に部屋を生成
    /// </summary>
    void CreateAllRoom();
    /// <summary>
    /// 指定したエリアに部屋を生成
    /// </summary>
    void CreateRoom(AreaData* area);
	/// <summary>
	/// すべての部屋同士をつなげる
	/// </summary>
	void ConnectAllRoom();
	/// <summary>
	/// 分割線マスまで掘り進める
	/// </summary>
	int DigToDivideLine(AreaData* area, MapConst::eDirectionFour direction);
	/// <summary>
	/// 分割線上で指定した座標同士の経路をつなぐ
	/// </summary>
	void ConnectDivideLine(int sartId, int goalLine);


	const std::vector<AreaData*>& GetAreaData() { return m_areas; }

	// 分割線のマスのIDリスト
	const std::vector<int>& GetDivideLine(){ return m_divideLines; }

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
	std::vector<AreaData*> m_areas;
	// 分割線のマスのIDリスト
	std::vector<int> m_divideLines;
	// エリアの分割回数
};
