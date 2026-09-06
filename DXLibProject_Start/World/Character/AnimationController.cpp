#include "pch.h"
#include "AnimationController.h"
#include"../../Utility/Vector3.h"

namespace {

	// アニメーションの再生速度
	constexpr float kPlaySpeed = 30;
}

AnimationController::AnimationController():
	m_attachIndex(-1),
	m_currentAnim(-1),
	m_nextAnim(-1),
	m_totalTime(0),
	m_playCount(0),
	m_isLoop(false),
	m_isPlaying(false),
	m_animSpeed(1),
	m_isForcePlay(false),
	m_blendRate(1)
{
}

AnimationController::AnimationController(ModelData* modelData)
{

}

AnimationController::~AnimationController()
{
	End();
}

void AnimationController::Init(ModelData* modelData)
{
	m_modelData = modelData;
}

void AnimationController::End()
{
}

void AnimationController::PlayAnimation(const Status::AnimData& data)
{
	// 割り込み再生不可能なら処理しない
	if (m_isForcePlay && m_isPlaying)return;
	// 同じアニメーションなら処理しない
	if (m_currentAnim == data.index && m_isPlaying)return;
	m_currentAnim = data.index;
	m_nextIndex = data.index;
	// すでに再生中なら一度アニメーションを外しておく
	if (m_attachIndex != -1) {
		MV1DetachAnim(m_modelData->GetHandle(), m_attachIndex);
	}

	// アニメーションのインデックスを更新
	m_attachIndex = MV1AttachAnim(m_modelData->GetHandle(), 0, m_modelData->GetAnimHandle()[m_nextIndex]);
	// アニメーションの総尺を取得
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelData->GetHandle(), m_attachIndex);
	// 現在のアニメーションを更新
	m_nextAnim = data.index;


	// アニメーションのループ設定を更新
	m_isLoop = data.isLoop;

	//割り込み再生不可能かどうかを設定
	m_isForcePlay = data.isForcePlay;

	// 再生中に
	m_isPlaying = true;
}

void AnimationController::Update(float deltaTime)
{
	m_playCountOld = m_playCount;
	// 再生していなければ即時rturn;
	if (!m_isPlaying)	return;
	// 再生時間の更新
	m_playCount += kPlaySpeed*m_animSpeed*deltaTime;

	// 再生時間が総尺を過ぎたら
	if (m_playCount > m_totalTime) {
		if (m_isLoop) {
			// ループアニメーションなら最初に戻る
			m_playCount = 0.0f;
		}
		else {
			// ワンショットアニメーションなら停止
			m_isPlaying = false;
			// 総尺で固定
			m_playCount = m_totalTime;
		}
	}


	// モデルに再生時間をセット
	MV1SetAttachAnimTime(m_modelData->GetHandle(), m_attachIndex, m_playCount);
}

AnimationController AnimationController::Duplicate()
{
	AnimationController duplicate;

	duplicate.m_modelData = m_modelData->Duplicate();

	return duplicate;
}

void AnimationController::Debug()
{
	printfDx("animation |    modeel   : %d\n", m_modelData->GetHandle());
	printfDx("animation | currentAnim : %d\n", m_currentAnim);
	printfDx("animation | m_playCount : %f\n", m_playCount);
	printfDx("animation | m_totalTime : %f\n", m_totalTime);
	printfDx("animation |    Index    : %d\n", m_attachIndex);
	printfDx("animation |   isLoop    : %s\n", m_isLoop?"ループ再生": "ワンショット");
	printfDx("animation |   isPlay    : %s\n", m_isPlaying?"再生中": "再生してない");
	printfDx("animation |    speed    : %f\n", m_animSpeed  );
	printfDx("animation |    blend    : %f\n", m_blendRate);
	for (int i = 0; i < m_modelData->GetAnimHandle().size(); i++) {
		printfDx("animation |animHandle[i]: %d\n", m_modelData->GetAnimHandle()[i]);

	}
}

bool AnimationController::CheckOverMoment(float time)
{
	if (m_playCount < time)return false;
	if (m_playCountOld > time)return false;
	return true;
}
