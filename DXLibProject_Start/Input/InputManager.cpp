#include "InputManager.h"
#include "InputConst.h"
#include "Input/Device/GamePad.h"
#include "Utility/Loder/CsvLoader.h"
namespace{ 
	constexpr int kRightTrigger = 10;
	constexpr int kLeftTrigger = 11;
	const char* const kDataPath = "KeyCode";
}
void InputManager::Init()
{
	m_keyParam = Data::Csv::LoadCsvAs<InputKeyParam>(kDataPath);
	for (int i = 0; i < 1; i++) {
		m_gamePad.push_back(std::make_unique<GamePad>(i));
	}
}

void InputManager::End()
{}

void InputManager::Update(float deltaTime)
{
	for (int i = 0; i < m_gamePad.size(); i++) {
		m_gamePad[i]->Update(deltaTime);
	}
}

bool InputManager::IsDown(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device=m_keyParam[static_cast<int>(key)].device;
	switch (device) {
	case Input::Device::GamePad:
		return m_gamePad[static_cast<int>(pad)]->IsDown(key);
		break;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return false;

}
bool InputManager::IsPressed(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device = m_keyParam[static_cast<int>(key)].device;
	switch (device) {
	case Input::Device::GamePad:
		return	m_gamePad[static_cast<int>(pad)]->IsPressed(key);
		break;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return false;

}
bool InputManager::IsReleased(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device = m_keyParam[static_cast<int>(key)].device;
	switch (device) {
	case Input::Device::GamePad:
		return 	m_gamePad[static_cast<int>(pad)]->IsReleased(key);
		break;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return false;

}

bool InputManager::IsHold(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device = m_keyParam[static_cast<int>(key)].device;
	switch (device) {
	case Input::Device::GamePad:
		return m_gamePad[static_cast<int>(pad)]->IsHold(key);
		break;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return false;
}

bool InputManager::IsDown(const Input::Action& action, const Input::GamePad& pad)
{

}


bool InputManager::IsPressed(const Input::Action& action)
{
}

bool InputManager::IsReleased(const Input::Action& action)
{
}

bool InputManager::IsHold(const Input::Action& action)
{
}
