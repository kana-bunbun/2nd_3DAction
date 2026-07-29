#pragma once
#include"UIObject.h"
#include<vector>
#include<string>
class TestMenu :public UIObject {
public:
	enum class MenuItem{
		GameStart,
		Option,
		Max
	};
public:
	TestMenu();
	~TestMenu()=default;

	void OnInit()override;
	void OnEnd()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
	const TestMenu::MenuItem& GetSelectItem();
private:
	/// <summary>
	/// メニュー項目
	/// </summary>
	std::vector<std::string> m_items;
	/// <summary>
	/// 選択中のインデックス
	/// </summary>
	int m_selectIndex;
};
