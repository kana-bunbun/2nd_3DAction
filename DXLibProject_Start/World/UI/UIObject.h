#pragma once
#include"../../Utility/Vector2.h"
/// <summary>
/// UIで扱うオブジェクトの基底クラス
/// </summary>
class UIObject
{
public:
	UIObject() :m_position(Vector2::Zero), m_visible(true) {};
	virtual ~UIObject() {};
	virtual void Init()=0;
	virtual void Update(float deltaTime) {};
	virtual void Draw() {};
	virtual void End()=0;
	void SetPosition(const Vector2& position) { m_position = position; }
	void SetVisible(bool visible) { m_visible = visible; }

	const Vector2& GetPosition()const { return m_position; }
	bool IsVisible() const{ return m_visible; }
protected:
	Vector2 m_position;
	bool m_visible;
};

