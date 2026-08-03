#pragma once
#include<string>

/// <summary>
/// 画像をオブジェクトとして扱うためのクラス
/// </summary>
class ImageResource
{
public:
	 ImageResource(int ID, int handle);
	 ~ImageResource();
	int GetHandle() { return m_handle; }
	int GetID() { return ID; }
public:
	int ID;
	/// <summary>
	/// 画像ハンドル
	/// </summary>
	int m_handle;
};
