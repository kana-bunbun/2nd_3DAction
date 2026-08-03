#pragma once
#include "../Core/UIObject.h"
#include"../../../Data/UITextParam.h"
#include<string>
/// <summary>
/// 汎用テキストUIオブジェクトクラス
/// </summary>
class UIText :public UIObject
{
public:
	UIText();
	UIText(const UITextParam& param);
	UIText(const std ::string& initText,const UITextParam& param);
	UIText(const std ::string& initText,const UITextParam& param,const Vector2& pos);
	virtual ~UIText()=default;

	
	// UIObjectクラスのメンバ関数
	void OnInit()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
	void OnEnd()override;

	// UITextクラスの固有処理
	void Build();

	void SetText(const std::string& text) { m_text = text; }
	
	void SetTextParam(const UITextParam& param) { m_param = param; }

protected:
	/// <summary>
	/// 表示する文字列
	/// </summary>
	std::string m_text;
	/// <summary>
	/// 選択中かどうか
	/// </summary>
	bool isSelected;
	UITextParam m_param;

	/// <summary>
	/// フォントハンドル
	/// </summary>
	int m_fontHandle;
};

