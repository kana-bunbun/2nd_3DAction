#pragma once
#include"../Core/UIObject.h"
#include"../../../System/ImageResource.h"
class UIItemCursor:public UIObject
{
public:
	UIItemCursor();
	~UIItemCursor()override = default;
	void OnInit();
	void OnEnd();
	void OnUpdatate(float deltaTime);
	void OnDraw();
	void SetLerpPosition(const Vector2& position) { m_desirePosition = position; }
	void SetPosition(const Vector2& position) { m_position = position; }
private:
	Vector2 m_desirePosition;
	float m_lerpCount;
	std::shared_ptr<ImageResource> m_image;
};

