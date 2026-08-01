#pragma once
#include"../UIScreen.h"
class UIText;
class UIGroup;
class UIImage;
class UIButton;
class TestScreen:public UIScreen
{
public:
	enum class ScreenState {
		Invalid,
		PressStay,
		ModeSelect,
		Max
	};
	enum class ButtonResult {
		None,
		Start,
		Option,
		Exit,
		Max
	};
public:
	TestScreen();
	~TestScreen()override=default;
	void Init()override;
	const ScreenState& GetState(){ return m_state; }
	void SetScreenState(const ScreenState& state) { m_state = state; }
	void ShowPressStay();
	void ShowModeSelect();

	// Sceneからの入力によって処理をする関数を用意
	// UIを管理するScreenクラスでは入力は行わない
	void SelectNextButton();
	void SelectPrevButton();
	void ExecuteButton();
	ButtonResult ConsumeResult();
private:
	// 個別で処理を行うためのポインタ
	UIText* m_pPressText;
	UIImage* m_pLogoImage;

	UIGroup* m_pGorupText;
	
	//UIText* m_pSelectStartText;
	//UIText* m_pSelectOptionText;
	//UIText* m_pSelectExitText;
	ScreenState m_state;
	// 現在選択中のインデックス
	int m_selectIndex;
	// ボタンの選択肢を管理する
	std::vector<UIButton*>m_selectButtons;
	/// <summary>
	/// 選択結果
	/// </summary>
	ButtonResult m_result;
};

