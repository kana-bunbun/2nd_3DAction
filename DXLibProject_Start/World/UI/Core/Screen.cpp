#include "Screen.h"

ScreenCommand Screen::ConsumeCommand()
{
    ScreenCommand command = m_command;
    m_command = ScreenCommand::None;
    return command;
}
