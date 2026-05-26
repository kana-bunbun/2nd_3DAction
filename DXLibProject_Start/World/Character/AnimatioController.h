#pragma once
#include"Animation.h"
#include<vector>

class AnimatioController
{
public:
	AnimatioController();
	~AnimatioController();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(int modelHandle);

	/// <summary>
	/// アニメーションを再生する関数
	/// </summary>
	/// <param name="data">アニメーションのデータ</param>
	void PlayAnimation(const Status::AnimData& data);
	/// <summary>
	/// アニメーションの再生カウントをリセットする関数
	/// </summary>
	void ResetPlayCount() { m_playCount = 0.0f; }
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// アニメーションを再生しているかどうかを返す関数
	/// </summary>
	/// <returns>再生中ならtrue</returns>
	bool IsPlaying() { return m_isPlaying; }

	/// <summary>
	/// デバッグ表示
	/// </summary>
	void Debug();

	/// <summary>
	/// アニメーションの再生カウントを取得する関数
	/// </summary>
	/// <returns></returns>
	float GetPlayCount() { return m_playCount; }
	/// <summary>
	/// 指定した時間を過ぎた瞬間かどうか
	/// </summary>
	/// <param name="time">指定した時間</param>
	/// <returns>過ぎた瞬間true</returns>
	bool CheckOverMoment(float time);
	/// <summary>
	/// アニメーションの才瀬尾速度を設定する関数
	/// </summary>
	/// <param name="speed">アニメーションの速さ(割合)</param>
	void SetAnimSpeed(float speed=1) { m_animSpeed = speed; }
	const float GetAnimSpeed()const { return m_animSpeed; }
	/// <summary>
	/// 割り込み不可能かどうかを取得する関数
	/// </summary>
	/// <returns>割り込み不可能の時true</returns>
	bool IsForcePlay() { return m_isForcePlay; }
	void AddAnim(int animHandle, int index = -1);
private:
	// モデルハンドル
	int m_modelHandle;
	// アニメーションの番号
	int m_attachIndex;
	int m_nextIndex;
	// 現在のアニメーションの番号
	int m_currentAnim;
	int m_nextAnim;
	// アニメーションの現在の再生時間
	float m_playCount;
	// 前回更新時のアニメーションの再生時間
	float m_playCountOld;
	// アニメーションの総尺
	float m_totalTime;
	// アニメーションがループするかどうか
	bool m_isLoop;
	// 現在アニメーションを再生している角か
	bool m_isPlaying;
	// アニメーションの再生スピード
	float m_animSpeed;
	// 割り込み再生不可能かどうか
	bool m_isForcePlay;
	// アニメーションのブレンド率
	float m_blendRate;
	// アニメーションのハンドル
	std::vector<int>m_animHandle;
};

