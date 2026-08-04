#include "ItemList.h"

ItemList::ItemList()
{

}

ItemList::~ItemList()
{

}

void ItemList::AddItem(const ItemData::Type & type, int addNum)
{
	// すでに同じアイテムを所持していたら加算する
	for (int i = 0; i < m_items.size(); i++) {
		ItemData::Type itemType = m_items[i].GetType();
		if(itemType != type)continue;
		// 同じアイテムを所持していたら加算して終了
		m_items[i].Add(addNum);
		return;
	}

	// 同じアイテムを所持していないとき
	// 空のアイテム枠があるか調べる
	for (int i = 0; i < m_items.size(); i++) {
		int holdNum = m_items[i].GetItemNum();
		// アイテムを所持数しているときcontinue
		if (holdNum)continue;
		// 空のアイテム枠があれば加算して終了
		m_items[i].Add(addNum);
		return;
	}
}

bool ItemList::CanAddItem(const ItemData::Type & type)
{
	for (int i = 0; i < m_items.size(); i++) {
		ItemData::Type itemType = m_items[i].GetType();
		if (itemType != ItemData::Type::Invalid && itemType != type)continue;
		return true;
	}
	return false;
}

void ItemList::UseItem(int itemIndex, int subNum)
{
	// アイテムを使用できるかどうかチェック
	if (!CanUseItem(itemIndex, subNum))return;
	// アイテムの消費
	m_items[itemIndex].Sub(subNum);
}

bool ItemList::CanUseItem(int itemIndex, int useCount)
{
	if (itemIndex < 0 || itemIndex >= m_items.size())return false;
	ItemData data = m_items[itemIndex];
	// 指定した番号でアイテムがなければfalse
	if (data.GetType()==ItemData::Type::Invalid)return false;
	// 指定した番号のアイテム所持数が消費数より少なければfalse
	if (data.GetItemNum()<useCount)return false;
	// ここまで来たら使用可能
	return true;
}


