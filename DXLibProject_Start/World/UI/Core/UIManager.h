#pragma once
#include<memory>
#include<vector>
#include"UIInput.h"
#include"UICommand.h"
class UIScreen;
/// <summary>
/// UIの管理を行う
/// 複数のUIScreenを同時に扱う際はstack構造で管理する
/// </summary>
class UIManager {
public:
	UIManager();
	~UIManager();
	/// <summary>
	/// 最前面のUIScreenを更新
	/// </summary>
	void Update(float deltaTime,const UIInput& uiInput);
	/// <summary>
	/// 管理しているUIScreenを描画
	/// </summary>
	void Draw();
	/// <summary>
	/// UIScreenを最前面に登録する
	/// </summary>
	void PushScreen(std::unique_ptr<UIScreen> pScreen);
	/// <summary>
	/// 最前面のUIScreenを解放する
	/// </summary>
	void PopScreen();
	/// <summary>
	/// 最前面のUIScreenを取得する
	/// </summary>
	/// <returns></returns>
	UIScreen* GetTopScreen();
	/// <summary>
	/// 管理中のUIScreenが空かどうか取得
	/// </summary>
	/// <returns></returns>
	bool Empty()const { return m_screens.empty(); }
	/// <summary>
	/// 最前面にあるコマンド取得後、値をリセット
	/// </summary>
	/// <returns></returns>
	UICommand ConsumeCommand();
private:

	/// <summary>
	/// 管理しているUIscreen群
	/// </summary>
	std::vector<std::unique_ptr<UIScreen>>m_screens;


};