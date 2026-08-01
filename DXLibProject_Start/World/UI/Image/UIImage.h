#pragma once
#include"../UIObject.h"

/// <summary>
/// 汎用画像UIオブジェクト
/// </summary>
class UIImage:public UIObject
{
public:
	UIImage();
	UIImage(int handle ,const Vector2& position);
	virtual ~UIImage()override = default;

	//
	void OnInit()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
	void OnEnd()override;
public:
	void SetGraphHandle(int handle) { m_graphHandle = handle; }
	int GetGraphHandle() { return m_graphHandle; }
private:
	//画像ハンドル
	int m_graphHandle;

};

