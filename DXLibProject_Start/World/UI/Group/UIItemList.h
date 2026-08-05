#pragma once
#include"../Object/UIItemSlot.h"
#include"../../Object/Item/ItemList.h"
#include"../Core/UIObject.h"
#include<array>
#include<memory>
/// <summary>
/// 所持アイテムリストのUI表示をする
/// </summary>
class UIItemList: public UIObject
{
public:
	UIItemList();
	void OnInit()override;
	void OnUpdate(float deltatime)override;
	void SelectPrevIndex();
	void SelectNextIndex();
private:
	int m_selectIndex;
	std::array<UIItemSlot*, kItemSlotNum> m_slots;
};

