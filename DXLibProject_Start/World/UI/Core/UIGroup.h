#pragma once
#include"UIObject.h"
/// <summary>
///  UIObjectをまとめて管理するクラス
/// 座標や表示をまとめて管理する
/// このクラスは描画する情報を持たない
/// </summary>
class UIGroup :public UIObject
{
public:
	UIGroup() = default;
	UIGroup(const Vector2& position) { SetPosition(position); }
	~UIGroup() = default;

protected:
	/// <summary>
	/// UIGroupクラスでは描画しない
	/// 空の処理にしておく
	/// </summary>
	void OnDraw()override {};
};

