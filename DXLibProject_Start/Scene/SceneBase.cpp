#include "SceneBase.h"
#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Vector3.h"
#include "../Utility/MyMath.h"
#include "../Utility/Time.h"

namespace {

	// フェード速度
	constexpr int kFadeSpeed = 5;
	constexpr int kFadeMax = 255;
}

// コンストラクタ
SceneBase::SceneBase() :
	m_fadeColor(Color::kBlack),
	m_fadeBright(kFadeMax),
	m_fadeSpeed(-kFadeSpeed),
	m_isFading(false)
{
}

// フェードの更新
void SceneBase::UpdateFade() {

	if (m_fadeSpeed == 0)return;
	m_fadeBright += kFadeMax * m_fadeSpeed *0.7f;
	// 値を地域内に収める
	m_fadeBright = MyMath::Clamp(m_fadeBright, 0, kFadeMax);

	if (m_fadeBright==0 && m_fadeSpeed < 0) {
		m_fadeSpeed = 0;
		m_isFading = false;
	}
	else if (m_fadeBright >= kFadeMax && m_fadeSpeed > 0) {
		m_fadeSpeed = 0;
		m_isFading = false;
	}
	else {
		m_isFading = true;
	}

}


// フェードの描画
void SceneBase::DrawFade() const {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// フェードイン中かどうかを判定
bool SceneBase::IsFadingIn() const { return (m_isFading && m_fadeSpeed < 0); }

// フェードアウト中かどうかを判定
bool SceneBase::IsFadingOut() const { return (m_isFading && m_fadeSpeed > 0); }

// フェード中かどうかを判定
bool SceneBase::IsFading() const { return m_isFading; }

// フェードアウト開始
void SceneBase::StartFadeOut() {
	m_fadeSpeed = kFadeSpeed;
	m_isFading = true;
}

// フェードイン開始
void SceneBase::StartFadeIn()
{
	
	m_fadeSpeed = -kFadeSpeed;
	m_isFading = true;
}
