#pragma once
#include"../Core/UIScreen.h"
#include"../Group/UIItemList.h"
class InGameMainScreen :public UIScreen
{
public:
	InGameMainScreen();
	~InGameMainScreen();
	void Init()override;
	void Update(float deltaTime, const InputData& input)override;
private:
	UIItemList* m_pItemList;
};

