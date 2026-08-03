#include "UIManager.h"
#include"UIScreen.h"
UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::Update(float deltaTime, const UIInput& uiInput)
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return;
	// 最前面のUIScreenを更新する
	m_screens.back()->Update(deltaTime,uiInput);
}

void UIManager::Draw()
{
	for (auto& screen : m_screens) {
		screen->Draw();
	}
}

void UIManager::PushScreen(std::unique_ptr<UIScreen> pScreen)
{
	// 渡されたUIScreenがnullptrなら即時return
	if (!pScreen)return;

	// 初期化
	pScreen->Init();
	// UIScreenを末尾に登録
	m_screens.emplace_back(std::move(pScreen));

}

void UIManager::PopScreen()
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return;
	// 管理しているUIScreenの末尾を削除
	m_screens.pop_back();
}

UIScreen* UIManager::GetTopScreen()
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return nullptr;
	// 最前面のUIScreenの生ポインタを返す
	return m_screens.back().get();
}

UICommand UIManager::ConsumeCommand()
{
	if (m_screens.empty())return UICommand::None;
	return m_screens.back()->ConsumeCommand();
}
