#pragma once
#include"../Object/Item/ItemData.h"
#include"../../Utility/Vector3.h"
#include"../../System/Resource.h"
class ItemSlot
{
public:
	ItemSlot();
	~ItemSlot();

	void Init();
	void Draw();
	void End();

	void Add();
	void Sub();
public:
	int GetHoldNum() { return m_holdNum; }
	void SetPosition(const Vector3& const position) { m_drawPos = position; }
	ItemData::Type GetItemType() { return m_itemData.GetType(); }
	void SetItemType(ItemData::Type type);
private:
	// 固定サイズの画像の大きさを取得
	float NormalizeGraphScale(int graphHandle);
public:
	ItemData m_itemData;
	bool m_select;
private:
	/// <summary>
	/// 所持数
	/// </summary>
	int m_holdNum;
	/// <summary>
	/// 画像データ
	/// </summary>
	GraphData* m_graphData;
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector3 m_drawPos;
};

