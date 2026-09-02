#pragma once
namespace Input{
	/// <summary>
	/// ボタン長押し判定に必要な時間のデフォルト値
	/// </summary>
	constexpr float kHoldDefaultCount = 0.5f;
	/// <summary>
	/// 1つのアクションごとのキーの最大数
	/// </summary>
	const int kActionKeyMax = 6;

	enum class Device {
		Invalid=-1,
		GamePad,
		Keyboard,
		Mouce,
		Max,
	};
	enum class Key{
		Invalid ,

		// ゲームパッドのボタン一覧====================================
		GpUp,	
		GpRight,
		GpDown,	
		GpLeft,	
		GpNorth,
		GpEast,
		GpSouth,
		GpWest,
		GpStart,
		GpBack,
		GpLeftShoulder,
		GpRightShoulder,
		GpLeftTrigger,
		GpRightTrigger,
		GpLeftThumb,
		GpRightThumb,
		// 左スティックの4方向入力
		GpLeftThumbUp,
		GpLeftThumbRight,
		GpLeftThumbDown,
		GpLeftThumbLeft,
		// 右スティックの4方向入力
		GpRightThumbUp,
		GpRightThumbRight,
		GpRightThumbDown,
		GpRightThumbLeft,
		// ゲームパッドの十字キー
		GpCross,
		// 左スティックの傾き
		GpLeftVector,
		// 右スティックの傾き
		GpRightVector,
		// ============================================================
		Max,
	};
	constexpr int kKeyMaxNum = static_cast<int>(Key::Max);
	// 入力アクション
	enum class Action {
		Invalid = -1,

		Up,
		Right,
		Down,
		Left,
		Decide,
		Cancel,
		Menu,
		Start,
		Move,
		SelectMove,
		Camera,
		DragonCall,
		Dash,
		Parry,
		Max,
	};
	enum class VectorAction {
		Invalid,
		Max,
	};

	enum GamePadKey {
		Invalid = -1,
		Up,
		Down,
		Left,
		Right,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		LeftTrigger,
		RightTrigger,
		South,
		East,
		West,
		North,
		LeftThumbUp,
		LeftThumbRight,
		LeftThumbDown,
		LeftThumbLeft,
		RightThumbUp,
		RightThumbRight,
		RightThumbDown,
		RightThumbLeft,
		Cross,
		LeftVector,
		RightVector,
		Max,
	};
	constexpr int kActionMaxNum = static_cast<int>(Action::Max);
	// キーの入力状態
	enum class KeyState {
		Invalid=-1,

		IsPressed,
		IsDown,
		IsReleased,

		Max,
	};
	// ゲームパッドの番号
	enum class GamePad {
		Invalid=-1,	// 不正値

		Pad1,
		Pad2,
		Pad3,
		Pad4,

		None,
		Max,
	};
	constexpr int kGamePadMaxNum = static_cast<int>(GamePad::Max);
	// スティックの種類
	enum class Thumb{
		Invalid=-1,
		Left,
		Right,
		Max,
	};
	// トリガーの種類
	enum class Trigger{
		Invalid=-1,
		Left,
		Right,
		Max,
	};

	enum class DirectionHolizontal{//水平方向
		Invalid=-1,
		Left,
		Right,
		Max,
	};
	enum class DirectionVertical{// 垂直方向
		Invalid=-1,
		Up,
		Down,
		Max,
	};



}