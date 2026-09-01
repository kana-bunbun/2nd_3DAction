#pragma once
#include"../Core/UIScreen.h"
class UIButton;
class UIGroup;
class PauseScreen:public UIScreen
{
public:
	enum class ButtonResult {
		None,
		Resume,
		Exit,
		Max,
	};
public:
	PauseScreen();
	~PauseScreen()override = default;
	void Init()override;
	void Draw()override;
	void Update(float deltaTime,const InputData& input)override;
	void SelectNextButton();
	void SelectPrevButton();
	void ExecuteButton();
	ButtonResult ConsumeResult();
private:
	UIButton* m_pButton;
	// 個別で処理を行うためのポインタ

	UIGroup* m_pGorupButtons;

	//UIText* m_pSelectStartText;
	//UIText* m_pSelectOptionText;
	//UIText* m_pSelectExitText;
	// 現在選択中のインデックス
	int m_selectIndex;
	// ボタンの選択肢を管理する
	std::vector<UIButton*>m_selectButtons;
	/// <summary>
	/// 選択結果
	/// </summary>
	ButtonResult m_result;
};

