#pragma once
#include<DxLib.h>
/// <summary>
/// 色のデータ
/// </summary>
namespace Color {
	/// <summary>
	/// 外部データで色を指定する時に受け皿になる構造体
	/// intで受け取ると整数データを受け取る際に影響が出るためこれで受け取る
	/// </summary>
	struct ColorData {
		int value;
	};

	// 色の情報を定義
	// 色の参照元
	// https://www.colordic.org/

	// 白
	constexpr int kWhite = 0xffffff;

	// 黒
	constexpr int kBlack = 0x000000;

	// グレー
	constexpr int kGray = 0x808080;

	// 赤
	constexpr int kRed = 0xff0000;

	// 緑
	constexpr int kGreen = 0x00ff00;

	// 青
	constexpr int kBlue = 0x0000ff;

	// イエロー
	constexpr int kYellow = 0xffff00;

	// シアン
	constexpr int kCyan = 0x00ffff;

	// マゼンタ
	constexpr int kMagenta = 0xff00ff;

}
struct Color_F {
public:
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 1.0f;
	COLOR_F ToCOLOR_F() { return{ red,green,blue,alpha }; }
	int ToColor() { return GetColor(static_cast<int>(255 * red), static_cast<int>(255 * green), static_cast<int>(255 * blue)); }
};