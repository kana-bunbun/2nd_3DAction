#pragma once

#include<vector>
#include<string>

// Dxライブラリではフォントのサイズ変更などは扱いづらい
// https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N7
// 少しでも使いやすくするために読み込み対応やデータ対応をしておく

/// <summary>
/// フォントの情報を管理するクラス
/// シングルトンで運用
/// </summary>
class FontManager
{
public:
	struct FontData
	{
		/// <summary>
		/// フォントのの名前
		/// </summary>
		std::string fontName;
		/// <summary>
		/// フォントのサイズ
		/// </summary>
		int size;
		/// <summary>
		/// フォントの太さ
		/// </summary>
		int thickness;
		/// <summary>
		/// フォントハンドル
		/// </summary>
		int handle;
	};
public:
	static FontManager& GetInstance();

	~FontManager() = default;

	void Init();
	void End();

	/// <summary>
	/// フォントの名前指定のフォントハンドル取得
	/// 指定した名前のフォントがなければ新たに生成
	/// </summary>
	int GetFontHandle(const std::string& fontName,int size,int thickness);

private:
	/// <summary>
	/// シングルトンなのでprivate
	/// </summary>
	FontManager()=default;

	// コピー禁止
	FontManager(const FontManager&) = delete;
	// コピー代入を禁止
	FontManager& operator=(const FontManager&) = delete;
	// ムーブ禁止
	FontManager(FontManager&&) = delete;
	// ムーブ代入禁止
	FontManager& operator= (const FontManager&&) = delete;
private:
	/// <summary>
	/// 管理しているデータ
	/// すでに生成されているものが保持される
	/// </summary>
	std::vector<FontData>m_fonts;
};

