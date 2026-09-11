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
	enum class Key {
		Invalid,

		// ゲームパッドのボタン一覧====================================
		Gp_Up,
		Gp_Right,
		Gp_Down,
		Gp_Left,
		Gp_North,
		Gp_East,
		Gp_South,
		Gp_West,
		Gp_Start,
		Gp_Back,
		Gp_LeftShoulderr,
		Gp_RightShoulder,
		Gp_LeftTrigger,
		Gp_RightTriggerr,
		Gp_LeftThumb,
		Gp_RightThumb,
		// 左スティックの4方向入力
		Gp_LeftThumbUp,
		Gp_LeftThumbRightt,
		Gp_LeftThumbDown,
		Gp_LeftThumbLeft,
		// 右スティックの4方向入力
		Gp_RightThumbUp,
		Gp_RightThumbRight,
		Gp_RightThumbDown,
		Gp_RightThumbLeft,
		// ゲームパッドの十字キー
		Gp_Cross,
		// 左スティックの傾き
		Gp_LeftVector,
		// 右スティックの傾き
		Gp_RightVector,
		// ============================================================

		// キーボートのキー一覧========================================

		KeyBoard_Back,	// バックスペースキー
		KeyBoard_Tab,	// タブキー
		KeyBoard_Return,	// エンターキー
		KeyBoard_LShift,	// 左シフトキー
		KeyBoard_RShift,	// 右シフトキー
		KeyBoard_LControl,	// 左コントロールキー
		KeyBoard_RControl,	// 右コントロールキー
		KeyBoard_Escape,	// エスケープキー
		KeyBoard_Space,	// スペースキー
		KeyBoard_PGUp,	// ＰａｇｅＵＰキー
		KeyBoard_PGDown,	// ＰａｇｅＤｏｗｎキー
		KeyBoard_End,	// エンドキー
		KeyBoard_Home,	// ホームキー
		KeyBoard_Left,	// 左キー
		KeyBoard_Up,	// 上キー
		KeyBoard_Right,	// 右キー
		KeyBoard_Down,	// 下キー
		KeyBoard_Insert,	// インサートキー
		KeyBoard_Delete,	// デリートキー
		KeyBoard_Minus,	// －キー
		KeyBoard_Yen,	// ￥キー
		KeyBoard_Prevtrack,	// ＾キー
		KeyBoard_Period,	// ．キー
		KeyBoard_Slash,	// ／キー
		KeyBoard_LAlt,	// 左ＡＬＴキー
		KeyBoard_RAlt,	// 右ＡＬＴキー
		KeyBoard_Scroll,	// ScrollLockキー
		KeyBoard_Semicolon,	// ；キー
		KeyBoard_Colon,	// ：キー
		KeyBoard_LBracket,	// ［キー
		KeyBoard_RBracket,	// ］キー
		KeyBoard_At,	// ＠キー
		KeyBoard_BackSlash,	// ＼キー
		KeyBoard_Comma,	// ，キー
		KeyBoard_CapsLock,	// CapsLockキー
		KeyBoard_Pause,	// PauseBreakキー
		KeyBoard_NumPad0,	// テンキー０
		KeyBoard_NumPad1,	// テンキー１
		KeyBoard_NumPad2,	// テンキー２
		KeyBoard_NumPad3,	// テンキー３
		KeyBoard_NumPad4,	// テンキー４
		KeyBoard_NumPad5,	// テンキー５
		KeyBoard_NumPad6,	// テンキー６
		KeyBoard_NumPad7,	// テンキー７
		KeyBoard_NumPad8,	// テンキー８
		KeyBoard_NumPad9,	// テンキー９
		KeyBoard_Multiply,	// テンキー＊キー
		KeyBoard_Add,	// テンキー＋キー
		KeyBoard_Subtract,	// テンキー－キー
		KeyBoard_DecimalECIMAL,	// テンキー．キー
		KeyBoard_Divide,	// テンキー／キー
		KeyBoard_NumPadEnter,	// テンキーのエンターキー
		KeyBoard_F1,	// Ｆ１キー
		KeyBoard_F2,	// Ｆ２キー
		KeyBoard_F3,	// Ｆ３キー
		KeyBoard_F4,	// Ｆ４キー
		KeyBoard_F5,	// Ｆ５キー
		KeyBoard_F6,	// Ｆ６キー
		KeyBoard_F7,	// Ｆ７キー
		KeyBoard_F8,	// Ｆ８キー
		KeyBoard_F9,	// Ｆ９キー
		KeyBoard_F10,	// Ｆ１０キー
		KeyBoard_F11,	// Ｆ１１キー
		KeyBoard_F12,	// Ｆ１２キー
		KeyBoard_A,	// Ａキー
		KeyBoard_B,	// Ｂキー
		KeyBoard_C,	// Ｃキー
		KeyBoard_D,	// Ｄキー
		KeyBoard_E,	// Ｅキー
		KeyBoard_F,	// Ｆキー
		KeyBoard_G,	// Ｇキー
		KeyBoard_H,	// Ｈキー
		KeyBoard_I,	// Ｉキー
		KeyBoard_J,	// Ｊキー
		KeyBoard_K,	// Ｋキー
		KeyBoard_L,	// Ｌキー
		KeyBoard_M,	// Ｍキー
		KeyBoard_N,	// Ｎキー
		KeyBoard_O,	// Ｏキー
		KeyBoard_P,	// Ｐキー
		KeyBoard_Q,	// Ｑキー
		KeyBoard_R,	// Ｒキー
		KeyBoard_S,	// Ｓキー
		KeyBoard_T,	// Ｔキー
		KeyBoard_U,	// Ｕキー
		KeyBoard_V,	// Ｖキー
		KeyBoard_W,	// Ｗキー
		KeyBoard_X,	// Ｘキー
		KeyBoard_Y,	// Ｙキー
		KeyBoard_Z,	// Ｚキー
		KeyBoard_0,	// ０キー
		KeyBoard_1,	// １キー
		KeyBoard_2,	// ２キー
		KeyBoard_3,	// ３キー
		KeyBoard_4,	// ４キー
		KeyBoard_5,	// ５キー
		KeyBoard_6,	// ６キー
		KeyBoard_7,	// ７キー
		KeyBoard_8,	// ８キー
		KeyBoard_9,	// ９キー
		// ============================================================
		Max,
	};
	struct DeviceKeyID {
		int keyID = -1;
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
		CursorMove,
		ItemCursorMove,
		UseItem,
		PickUpItem,
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