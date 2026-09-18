#include "pch.h"
#include "ItemUseController.h"
#include "World/UI/Group/UIItemList.h"

ItemUseController::ItemUseController(UIItemList* _itemList)
{
	m_itemList = _itemList;
	ItemListController::Init();
}


void ItemUseController::UpdateAction(float deltaTime, const InputData& _inputData)
{
	if (_inputData.IsPressed(Input::Action::UseItem)) {
		m_itemList->UseItem();
	}
}
