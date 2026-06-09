#include <cassert>
#include "SceneManager.h"
#include "SceneTest.h"
#include "../Utility/Input.h"

SceneManager::SceneManager() {

	m_pCurrentScene = nullptr;
}

SceneManager::~SceneManager() {}

void SceneManager::Init() {

	m_pCurrentScene = std::make_unique<SceneTest>();
	m_pCurrentScene->Init();

}

void SceneManager::End() {

	// 確認処理
	assert(m_pCurrentScene);
	if (m_pCurrentScene) {
	m_pCurrentScene->End();
	m_pCurrentScene.reset();
	}
	if (m_pNextScene) {
		m_pNextScene->End();
		m_pNextScene.reset();
	}
}

void SceneManager::Update() {


	// 確認処理
	assert(m_pCurrentScene);
	if (!m_pCurrentScene) return;

	// フェード処理
	m_pCurrentScene->SceneBase::UpdateFade();

	// シーンの更新処理
	if (!m_pNextScene) {
		m_pNextScene = m_pCurrentScene->Update();
		if (m_pNextScene) {
			m_pCurrentScene->SceneBase::StartFadeOut();
		}
	}

	// フェードアウトが完了していたら後処理
	if (m_pNextScene && !m_pCurrentScene->IsFading()) {
		m_pCurrentScene->End();
		m_pCurrentScene = std::move(m_pNextScene);
		m_pCurrentScene->Init();
		m_pCurrentScene->SceneBase::StartFadeIn();
	}

	////if ( pScene != m_pCurrentScene ) {

	//	m_pCurrentScene->End();
	//	//delete m_pCurrentScene;

	//	// ポインタを初期化
	//	m_pCurrentScene = pScene;
	//	m_pCurrentScene->Init();
	//}

}

void SceneManager::Draw() {

	// 確認処理
	assert(m_pCurrentScene);
	if (!m_pCurrentScene) return;

	m_pCurrentScene->Draw();
	m_pCurrentScene->SceneBase::DrawFade();
}

