#include "pch.h"
#include "ItemUseController.h"

ItemUseController::ItemUseController(UIItemList* _itemList)
{
}

void ItemUseController::Update(float deltaTime, const InputData& _inputData)
{
	ItemListController::UpdateMoveCursor(deltaTime, _inputData);

	//if(_inputData)
}

void ItemUseController::UpdateAction(float deltaTime, InputData _inputData)
{}
