#pragma once
#include"../Core/UIObject.h"
#include"../../../System/ImageResource.h"
#include"../../../Utility/Vector2.h"
/// <summary>
/// 汎用画像UIオブジェクト
/// </summary>
class UIImage:public UIObject
{
public:
	UIImage();
	UIImage(std::shared_ptr<ImageResource> image ,const Vector2& position);
	virtual ~UIImage()override = default;

	//
	void OnInit()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
	void OnEnd()override;
public:
	void SetGraphHandle(std::shared_ptr<ImageResource> image) { m_image = image; }
	std::shared_ptr<ImageResource> GetGraphHandle() { return m_image; }
private:
	//画像ハンドル
	std::shared_ptr<ImageResource> m_image;

};

