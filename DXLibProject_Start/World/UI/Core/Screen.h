#pragma once
#include"Input/InputData.h"
#include"ScreenCommand.h"
class Screen
{
public:
	Screen() = default;
	virtual ~Screen() = default;

	virtual void Init() {};
	virtual void Update(float deltaTime, const InputData& input) {};
	virtual void Draw() {};
	virtual ScreenCommand ConsumeCommand();
protected:
	/// <summary>
	/// 外部に送るUIのコマンド
	/// </summary>
	ScreenCommand m_command = ScreenCommand::None;
};

