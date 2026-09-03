#pragma once
#include"Input/InputData.h"
#include"../ScreenCommand.h"
class Screen
{
public:
	Screen() = default;
	virtual ~Screen() = default;

	virtual void Init() {};
	virtual void Update(float deltaTime, const InputData& input) {};
	virtual void Draw() {};
	virtual UI::Command ConsumeCommand();
protected:
	/// <summary>
	/// 外部に送るUIのコマンド
	/// </summary>
	UI::Command m_command = UI::Command::None;

};

