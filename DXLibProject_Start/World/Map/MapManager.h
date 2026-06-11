#pragma once
#include<vector>
#include<memory>
#include"../../Utility/Vector3.h"
#include "MapTile.h";
#include "MapConst.h";
//#include"MapCreate.h"
#include<functional>
class MapCreate;
class RoomData;
class MapManager
{
public:
	static MapManager& GetInstance();
	void Initialize();
	/// <summary>
	/// 座標からIDを取得
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	int PositionToID(int posX, int posY);
	/// <summary>
	/// IDから座標を取得
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	int IDToPosX(size_t ID);
	int IDToPosY(size_t ID);
	/// <summary>
	/// IDを指定したタイル取得
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	MapTile* GetTile(int ID);
	/// <summary>
	/// 座標を指定しタイル取得
	/// </summary>
	MapTile* GetTile(int posX, int posY);
	/// <summary>
	/// 指定座標のマスから見た指定方向マスのポインタ取得
	/// </summary>
	MapTile* GetToDirSquare(int x, int y, MapConst::eDirectionFour direction);
		/// <summary>
	/// 指定した座標から指定した方向にあるマスの座標取得
	/// </summary>
	void ToDirPosition(int& x, int& y, MapConst::eDirectionFour direction);

	/// <summary>
	/// すべてのマスに行う処理を適応する
	/// 関数ポインタを使う
	/// </summary>
	/// <param name="action"></param>
	void ExecuteAllSquare(std::function<void(MapTile*)>& action);
	/// <summary>
	/// 部屋の追加
	/// </summary>
	void AddRoom(std::vector<int> idList);

	/// <summary>
	/// 使用可能な部屋取得
	/// </summary>
	/// <returns></returns>
	RoomData* GetCanUseRoom();

	/// <summary>
	/// 部屋の破棄
	/// </summary>
	void RemoveAllRoom();

	void SetFirstWall();
	void SetInvalid();
private:
	// シングルトンにするのでprivate
	MapManager() = default;
	// コピー禁止
	MapManager(const MapManager&) = delete;
	// コピー代入を禁止
	MapManager& operator=(const MapManager&) = delete;
	// ムーブ禁止
	MapManager(MapManager&&) = delete;
	// ムーブ代入禁止
	MapManager& operator= (const MapManager&&) = delete;

private:
	/// <summary>
	/// 管理中のマスオブジェクト配列
	/// </summary>
	std::vector<std::unique_ptr<MapTile>>m_mapData;

	std::vector <std::unique_ptr<RoomData>> m_rooms;
	std::vector<std::unique_ptr<RoomData>>m_unUseRooms;

};

