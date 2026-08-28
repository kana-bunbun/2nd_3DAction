#include "InputManager.h"
#include "InputConst.h"
#include "Input/Device/GamePad.h"
#include "Utility/Loder/CsvLoader.h"
#include "Data/InputKeyParam.h"
#include "Data/ActionKeyParam.h"
namespace{ 
	constexpr int kRightTrigger = 10;
	constexpr int kLeftTrigger = 11;
	const char* const kKeyDataPath = "KeyCode";
	const char* const kActionDataPath = "ActionKey";
	/// <summary>
	/// 入力の情報
	/// </summary>
	static std::vector <std::unique_ptr<GamePad>>m_gamePad;
	/// <summary>
	/// キーの情報
	/// </summary>
	static std::vector <InputKeyParam>m_keyParam;
	/// <summary>
	/// アクションごとのキー情報
	/// </summary>
	static std::vector<ActionKeyParam>m_actionParam;
}
InputManager::InputManager()
{
	Init();
}
void InputManager::Init()
{
	m_keyParam = Data::Csv::LoadCsvAs<InputKeyParam>(kKeyDataPath);
	m_actionParam = Data::Csv::LoadCsvAs<ActionKeyParam>(kActionDataPath);
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
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_actionParam.size())) {
		assert(false && "IsDown key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		return 	m_gamePad[static_cast<int>(pad)]->IsDown(keyID);
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
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_actionParam.size())) {
		assert(false && "IsPressed key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		return 	m_gamePad[static_cast<int>(pad)]->IsPressed(keyID);
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
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_actionParam.size())) {
		assert(false && "IsReleased key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		return 	m_gamePad[static_cast<int>(pad)]->IsReleased(keyID);
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
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_actionParam.size())) {
		assert(false && "IdHold key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		return 	m_gamePad[static_cast<int>(pad)]->IsHold(keyID);
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
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsDown action Out Of Range");
	}
	for (int i = 0; i < m_actionParam[actionIndex].keys.size();i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];

		if (IsDown(key, pad))return true;
	}
	return false;
}


bool InputManager::IsPressed(const Input::Action& action, const Input::GamePad& pad)
{
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsPressed action Out Of Range");
	}
	for (int i = 0; i < m_actionParam[actionIndex].keys.size(); i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];

		if (IsPressed(key, pad))return true;
	}
	return false;
}

bool InputManager::IsReleased(const Input::Action& action, const Input::GamePad& pad)
{
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsReleased action Out Of Range");
	}
	for (int i = 0; i < m_actionParam[actionIndex].keys.size(); i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];

		if (IsReleased(key, pad))return true;
	}
	return false;
}

bool InputManager::IsHold(const Input::Action& action, const Input::GamePad& pad)
{
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsHold action Out Of Range");
	}
	for (int i = 0; i < m_actionParam[actionIndex].keys.size(); i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];

		if (IsHold(key, pad))return true;
	}
	return false;
}
