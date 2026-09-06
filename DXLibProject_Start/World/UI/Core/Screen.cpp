#include"pch.h"
#include "Screen.h"

UI::Command Screen::ConsumeCommand()
{
    UI::Command command = m_command;
    m_command = UI::Command::None;
    return command;
}
