#include "pch.h"
#include "ItenBlendController.h"
#include "World/UI/Group/UIItemList.h"

ItenBlendController::ItenBlendController(UIItemList* _itemList)
{
	m_itemList = _itemList;
	ItemListController::Init();
}

void ItenBlendController::UpdateAction(float deltaTime, const InputData & _inputData)
{
	if (_inputData.IsPressed(Input::Action::Decide)) {
		m_itemList->Select();
	}
	if (_inputData.IsPressed(Input::Action::BlendItem)) {
		m_itemList->Blend();
	}
}
