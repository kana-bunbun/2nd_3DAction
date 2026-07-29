#include "FontManager.h"
#include<DxLib.h>

FontManager& FontManager::GetInstance()
{
	static FontManager instance;
	return instance;
}

void FontManager::Init()
{

}

void FontManager::End()
{
	for (auto& font : m_fonts) {
		if (font.handle == -1)continue;

		DeleteFontToHandle(font.handle);
		font.handle = -1;
	}
	m_fonts.clear();
}

int FontManager::GetFontHandle(const std::string & fontName, int size, int thickness)
{
	// 同じ設定のフォントがあるかどうかチェック
	for (const auto& font : m_fonts) {
		bool isSameFontName = (font.fontName == fontName);
		bool isSameSize = (font.size == size);
		bool isSameThickness = (font.thickness == thickness);
		// 同じものがあれば返す
		if (!isSameFontName || !isSameSize || !isSameThickness)continue;
		return font.handle;
	}
	// 同じ設定のデータがなければフォント生成
	int handle = CreateFontToHandle(fontName.c_str(), size, thickness);
	FontData newFont;
	newFont.fontName = fontName;
	newFont.size = size;
	newFont.thickness = thickness;
	newFont.handle = handle;
	// フォントの配列に登録
	m_fonts.emplace_back(newFont);

	return handle;
}
