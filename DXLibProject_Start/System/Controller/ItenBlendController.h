#pragma once
#include"ItemListController.h"
class ItenBlendController:ItemListController
{
public:
	ItenBlendController(UIItemList* _itemList);
	void UpdateAction(float deltaTime, const InputData& _inputData)override;
};

