#pragma once
#include"../Core/UIObject.h"
#include"../../../System/ImageResource.h"
class UIItemCursor:public UIObject
{
public:
	UIItemCursor();
	~UIItemCursor()override = default;
	void OnInit()override;
	void OnEnd()override;
	void OnUpdate(float deltaTime, const InputData& inputData)override;
	void OnDraw()override;
	void SetLerpPosition(const Vector2& position) { m_desirePosition = position; }
	void SetPosition(const Vector2& position) { m_position = position; }
private:
	Vector2 m_desirePosition;
	float m_lerpCount;
	std::shared_ptr<ImageResource> m_image;
};

