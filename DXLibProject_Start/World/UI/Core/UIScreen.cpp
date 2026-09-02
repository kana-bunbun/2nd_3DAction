#include "UIScreen.h"

void UIScreen::Update(float deltaTime, const InputData& input)
{

	for (auto& object : m_rootObjects) {
		if (!object)continue;
		object->Update(deltaTime,input);
	}
}

void UIScreen::Draw()
{
	for (auto& object : m_rootObjects) {
		if (!object)continue;
		object->Draw();
	}
}

ScreenCommand UIScreen::ConsumeCommand()
{
	ScreenCommand command = m_command;
	m_command = ScreenCommand::None;
	return command;
}

void UIScreen::AddUIObject(std::unique_ptr<UIObject> object)
{
	// 空ならreturn
	if (!object)return;
	object->Init();
	m_rootObjects.emplace_back(std::move(object));
}
