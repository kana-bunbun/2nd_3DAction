#include"pch.h"
#include "UIButton.h"
UIButton::UIButton():
m_isSelected(false)
{
}

void UIButton::OnDraw()
{

}

void UIButton::Execute()
{
	if (!m_onClick) {
		assert(false && "UIButton : Execute : onClick is unset");
		return;
		// 補足
		// UIButtonクラスは画像と文字を組み合わせたUIを想定している
		// その中でも選択肢としての使用を想定している
		// ただし、選択しても何もないUIとして使用する可能性もある
		// 必要に応じてm_onClickのチェック内容は変更する可能性がある
	}
	m_onClick();
}
