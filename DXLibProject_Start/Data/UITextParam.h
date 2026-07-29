#pragma once
#include<string>
/// <summary>
/// UITextの見た目の関する情報をまとめた構造体
/// </summary>
class UITextParam {
public:
	/// <summary>
	/// フォントの名前
	/// </summary>
	std::string fontName;
	/// <summary>
	/// 未選択時の色
	/// </summary>
	int normalColor;
	/// <summary>
	/// 選択時の色
	/// </summary>
	int selectedColor;
	/// <summary>
	/// フォントの大きさ
	/// </summary>
	int fontSize;
	/// <summary>
	/// フォントの太さ
	/// </summary>
	int thickness;
};