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

}

int FontManager::GetFontHandle(const std::string & fontName, int size, int thickness)
{
	for (const auto& font : m_fonts) {
		bool isSameFontName = (font.fontName == fontName);
		bool isSameSize = (font.size == size);
		bool isSameThickness = (font.thickness== thickness);
		if (isSameFontName && isSameSize && isSameThickness)
			return font.handle;
	}
	int handle = CreateFontToHandle(fontName.c_str(), size, thickness);
	FontData newFont;
	newFont.fontName = fontName;
	newFont.size = size;
	newFont.thickness = thickness;
	newFont.handle = handle;
	m_fonts.push_back(newFont);

	return handle;
}
