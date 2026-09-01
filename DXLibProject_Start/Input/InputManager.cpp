#include "InputManager.h"
#include "InputConst.h"
#include "Input/Device/GamePad.h"
#include "Utility/Loder/CsvLoader.h"
#include "Data/InputKeyParam.h"
#include "Data/ActionKeyParam.h"
#include "Input/ActionInputState.h"
#include "Input/InputData.h"
#include<array>
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
	/// <summary>
	/// 全アクションの入力情報
	/// </summary>
	static InputData m_inputData;
}
void InputManager::Init()
{
	m_keyParam = Data::Csv::LoadCsvAs<InputKeyParam>(kKeyDataPath);
	m_actionParam = Data::Csv::LoadCsvAs<ActionKeyParam>(kActionDataPath);
	for (int i = 0; i < 1; i++) {
		m_gamePad.push_back(std::make_unique<GamePad>(i+1));
	}
}

void InputManager::End()
{}

void InputManager::Update(float deltaTime)
{
	for (int i = 0; i < m_gamePad.size(); i++) {
		m_gamePad[i]->Update(deltaTime);
	}
	// 全アクション入力情報の更新
	UpdateInputData();
}

bool InputManager::IsDown(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device=m_keyParam[static_cast<int>(key)].device;
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "IsDown key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
	{
		int padID=static_cast<int>(pad);
		if (pad == Input::GamePad::None)padID = static_cast<int>(Input::GamePad::Pad1);
		if (m_gamePad[padID]->IsDown(keyID))return true;
		break;
	}
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
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "IsPressed key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		if (m_gamePad[static_cast<int>(pad)]->IsPressed(keyID))return true;
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
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "IsReleased key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		if(m_gamePad[static_cast<int>(pad)]->IsReleased(keyID))return true;
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
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "IdHold key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		if(m_gamePad[static_cast<int>(pad)]->IsHold(keyID))return true;
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

		if (IsPressed(key, pad))
			return true;
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

Vector2 InputManager::GetVector(const Input::Action& action, const Input::GamePad& pad)
{
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsHold action Out Of Range");
	}
	Vector2 max = Vector2::Zero;
	for (int i = 0; i < m_actionParam[actionIndex].keys.size(); i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];
		Vector2 vec = GetVector(key, pad);

		if (max.GetSqLength() < vec.GetSqLength())
			max = vec;
	}
	return max;
}

Vector2 InputManager::GetVector(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device = m_keyParam[static_cast<int>(key)].device;
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "GetVector key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:{}
		return m_gamePad[static_cast<int>(pad)]->GetVectorState(keyID).vector;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return Vector2::Zero;
}

const InputData InputManager::GetInputData()
{
	return m_inputData;
}

void InputManager::UpdateInputData()
{
	std::array<ActionInputState,static_cast<int>(Input::Action::Max)> inputData;
	std::array<VectorState,static_cast<int>(Input::Action::Max)> radian;
	// 全アクションの入力情報を調べる
	for (int i = 0; i < static_cast<int>(Input::Action::Max); i++) {
		// アクションを取得
		Input::Action action = static_cast<Input::Action>(i);
		// アクションの入力を設定
		inputData[i] = ActionInputState(IsDown(action), IsPressed(action), IsReleased(action), IsHold(action));
		radian[i] = GetVectorState(action);
	}
	// 入力情報の設定
	m_inputData.Init(inputData,radian);
}

VectorState InputManager::GetVectorState(const Input::Action& action, const Input::GamePad& pad)
{
	int actionIndex = static_cast<int>(action);
	if (actionIndex < 0 || actionIndex >= m_actionParam.size()) {

		assert(false && "IsHold action Out Of Range");
	}
	VectorState max = VectorState();
	for (int i = 0; i < m_actionParam[actionIndex].keys.size(); i++) {
		Input::Key key = m_actionParam[actionIndex].keys[i];
		VectorState state = GetVectorState(key, pad);

		if (max.vector.GetSqLength() < state.vector.GetSqLength())
			max = state;
	}
	return max;
}

VectorState InputManager::GetVectorState(const Input::Key& key, const Input::GamePad& pad)
{
	Input::Device device = m_keyParam[static_cast<int>(key)].device;
	int keyIndex = static_cast<int>(key);
	if (keyIndex < 0 || keyIndex >= static_cast<int>(m_keyParam.size())) {
		assert(false && "GetVector key OutOfRange");
	}
	int keyID = m_keyParam[keyIndex].keyID;
	switch (device) {
	case Input::Device::GamePad:
		return m_gamePad[static_cast<int>(pad)]->GetVectorState(keyID);

		break;
	case Input::Device::Keyboard:
		break;
	case Input::Device::Mouce:
		break;
	}
	return VectorState();
}