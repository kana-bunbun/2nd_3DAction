#pragma once
#include "../SceneBase.h"
class UIText;
class TestScreen;
class SceneTextTest :public SceneBase
{
public:
	SceneTextTest();
	~SceneTextTest()override = default;

	void Init()override;
	void End()override;
	std::unique_ptr<SceneBase>Update(float deltaTime)override;
	void Draw()override;
private:
	std::unique_ptr<TestScreen> m_pScreen;
	int m_textNameIndex;
};

