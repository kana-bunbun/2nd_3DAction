#pragma once
#include "../SceneBase.h"
#include<memory>
class CameraManager;
class SceneCollisionTest : public SceneBase
{
public:
	SceneCollisionTest();
	~SceneCollisionTest()override=default;

	void Init()override;
	void End()override;
	std::unique_ptr<SceneBase>Update(float deltaTime)override;
	void Draw()override;

private:

	void DrawGround();

	std::unique_ptr<CameraManager> m_pCameraManager;

};

