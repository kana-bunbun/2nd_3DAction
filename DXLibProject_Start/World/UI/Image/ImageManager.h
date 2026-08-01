#pragma once
#include<string>
#include<vector>
class ImageManager
{
public:
	struct ImageData {
		/// <summary>
		/// 画像のデータ名
		/// </summary>
		std::string fileName;
		/// <summary>
		/// 画像ハンドル
		/// </summary>
		int handle;
	};
public:
	static ImageManager& GetInstance();
	~ImageManager() = default;
	void Init();
	void End();
	int GetGraphHandle(const std::string name);
private:
	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	ImageManager(ImageManager&&) = delete;
	ImageManager& operator=(const ImageManager&&) = delete;
private:
	/// <summary>
	/// 管理している画像データ
	/// </summary>
	std::vector<ImageData>m_images;
};

