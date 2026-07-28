#pragma once
#include"SceneBase.h"
#include<memory>
class TitleLogo;
class TestText;
class TestMenu;
class SceneUITest :public SceneBase
{
public:
	enum class SceneState {
		PressAnyButton,
		MenuSelect,
		Max,
	};
public:
	SceneUITest();
	~SceneUITest()override = default;

	void Init()override;
	void End()override;
	std::unique_ptr<SceneBase>Update(float deltaTime)override;
	void Draw()override;
	

private:
	std::unique_ptr<TitleLogo> m_pLogo;
	std::unique_ptr<TestText> m_pText;
	std::unique_ptr<TestMenu> m_pTestMenu;
	SceneState m_state;
};

