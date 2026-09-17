#pragma once
#include"ItemListController.h"
class ItemUseController:public ItemListController
{
public:
	ItemUseController(UIItemList* _itemList);
	void Update(float deltaTime, const InputData& _inputData);
	void UpdateAction(float deltaTime,InputData _inputData);
};

