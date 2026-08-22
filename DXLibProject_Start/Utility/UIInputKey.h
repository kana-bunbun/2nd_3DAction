#pragma once

class UIInputKey {
public:
	enum State {
		CurrentState,
		PrevState,
		Max
	};
	/// <summary>
	/// ‰Ÿ‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©æ“¾
	/// </summary>
	bool IsDown() { return keyState[State::CurrentState]; }
	/// <summary>
	/// ‰Ÿ‚µ‚½uŠÔ‚©‚Ç‚¤‚©æ“¾
	/// </summary>
	bool IsPressed() { return keyState[State::CurrentState] && !keyState[State::PrevState]; }
	/// <summary>
	/// —£‚µ‚½uŠÔ‚©‚Ç‚¤‚©æ“¾
	/// </summary>
	bool IsReleased() { return !keyState[State::CurrentState] && keyState[State::PrevState]; }

	//bool IsHold() { return Input:: }

	bool keyState[State::Max] = { false,false };

};