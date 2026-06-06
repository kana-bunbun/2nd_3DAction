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
		Vector3 start = Vector3::zero;
		Vector3 size = Vector3::zero;
		AreaData()=default;
		AreaData(Vector3 start, Vector3 size) :start(start), size(size) {}
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
	void AddDevideLine(MapTile* tile);
	void DevideAreaFixCount();
	void DevideArea(AreaData devideArea, bool isVertical);
	void DevideAreaVertical(AreaData devideArea);
	void DevideAreaHorizontal(AreaData devideArea);
	AreaData GetMaxSizeArea();
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
	std::vector<AreaData> m_areaData;
	// 分割線のマスのIDリスト
	std::vector<int> m_devideLine;
	// エリアの分割回数
};

	const int _AREA_DEVIDE_COUNT = 8;
	// 最小部屋サイズ
	const int _MIN_ROOM_SIZE = 3;
