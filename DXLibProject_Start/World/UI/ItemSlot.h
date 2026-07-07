#pragma once
#include"../Object/Item/BlendManager.h"
#include"../../Utility/Vector3.h"
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
	void SetItemType(BlendManager::Type itemType);
	int GetHoldNum() { return m_holdNum; }
	void SetPosition(const Vector3& const position) { m_drawPos = position; }
private:
	// 固定サイズの画像の大きさを取得
	float NormalizeGraphScale(int graphHandle);
public:
	BlendManager::Type m_type;
	bool m_select;
private:
	/// <summary>
	/// 所持数
	/// </summary>
	int m_holdNum;
	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int graphHandle;
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector3 m_drawPos;
};

