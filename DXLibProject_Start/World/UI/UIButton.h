#pragma once
#include"UIGroup.h"
#include<functional>
class UIButton:public UIGroup
{
public:
	UIButton();
	virtual ~UIButton()override =default;

	/// <summary>
	/// 決定時の処理を設定
	/// </summary>
	/// <param name="onclick"></param>
	void SetOnClick(const std::function<void()>& onclick) { m_onClick = onclick; }
	/// <summary>
	/// 決定時の処理を実行
	/// </summary>
	void Execute();
protected:
	void OnDraw()override;
	void Selected(bool selected) { m_isSelected = selected; }
	bool IsSelected()const { return m_isSelected; }
private:
	bool m_isSelected;

	std::function<void()>m_onClick;


};

