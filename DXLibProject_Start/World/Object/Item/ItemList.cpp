#include "ItemList.h"
#include<DxLib.h>
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
		m_items[i].SetType(type);
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

	if (m_items[itemIndex].GetItemNum() > 0)return;
	// アイテムの所持数が無くなったらアイテムの種類を不正値に設定
	m_items[itemIndex].SetType(ItemData::Type::Invalid);
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

const ItemData& ItemList::GetItemData(int ID) const
{
	if (ID < 0 || ID >= m_items.size())return ItemData();
	return m_items[ID];
}

void ItemList::Debug()
{
	printfDx("ItemData::Type::Honey : %d\n",m_items[static_cast<int>(ItemData::Type::Honey)].GetItemNum());
	printfDx("ItemData::Type::Jam : %d\n",m_items[static_cast<int>(ItemData::Type::Jam)].GetItemNum());
	printfDx("ItemData::Type::ChiliPepper : %d\n", m_items[static_cast<int>(ItemData::Type::ChiliPepper)].GetItemNum());
	printfDx("ItemData::Type::Whiskey : %d\n", m_items[static_cast<int>(ItemData::Type::Whiskey)].GetItemNum());
	printfDx("ItemData::Type::HealBottle : %d\n", m_items[static_cast<int>(ItemData::Type::HealBottle)].GetItemNum());
	printfDx("ItemData::Type::FireBottle : %d\n", m_items[static_cast<int>(ItemData::Type::FireBottle)].GetItemNum());
}


