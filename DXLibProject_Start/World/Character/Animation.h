#pragma once

namespace Status {

	/// <summary>
	/// プレイヤーのアニメーションID
	/// ここの名前はある程度自分でわかりやすい名前にしてもいい
	/// </summary>
	enum class Player {

		Neutral = 0,
		Walk,
		Parry,
		Damage,
		Dead,
		Max
	};
	enum class Dragon {

		Neutral = 0,
		Move,
		Attack,
		Damage,
		Dead,
		Max
	};
	enum class Queen {
		Neutral = 0,
		Roar,
		Walk,
		run,
		Attack,
		JumpAttack,
		Damage,
		Dead,
		Max
	};
	/// <summary>
	/// 蜂のアニメーションID
	/// </summary>
	enum class Bee {

		Attack = 0,
		Death,
		Fly,
		Hit,
		Max
	};



	/// <summary>
	/// アニメーションのデータ
	/// </summary>
	struct AnimData {
		int index;			// アニメーションの番号
		bool isLoop;		// ループするかどうか
		bool isForcePlay;	// アニメーションの割り込み再生を許可するかどうか
	};
}