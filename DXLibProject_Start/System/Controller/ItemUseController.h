#pragma once
#include"ItemListController.h"
class ItemUseController:public ItemListController
{
public:
	ItemUseController(UIItemList* _itemList);
	void UpdateAction(float deltaTime,const InputData& _inputData)override;
};

