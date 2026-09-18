#pragma once
#include "Controller.h"
#include "World/Action/ActionInterval.h"

class UIItemList;

class ItemListController :public Controller
{
public:
	ItemListController() = default;
	ItemListController(UIItemList* _itemLlist);
	void Init()override;
	void SetItemList(UIItemList* _itemLlist);
	void Update(float deltaTime, const InputData& _inputData)override;
	void UpdateMoveCursor(float deltaTime, const InputData& _inputData);
	virtual void UpdateAction(float deltaTime, const InputData& _inputData) {};
protected:
	ActionInterval m_cursorInterval;
	UIItemList* m_itemList;
};

