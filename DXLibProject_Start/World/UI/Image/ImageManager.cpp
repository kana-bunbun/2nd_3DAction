#include "ImageManager.h"
#include<DxLib.h>
namespace{
}
ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

void ImageManager::Init()
{

}

void ImageManager::End()
{
	for (auto& image : m_images) {
		if (image.handle == -1)continue;
		DeleteGraph(image.handle);
		image.handle = -1;
	}
}

int ImageManager::GetGraphHandle(const std::string name)
{
	// 同じデータを読み込んでいないかどうかチェック
	for (const auto& image : m_images) {
		if (image.fileName != name)continue;
		return image.handle;
	}
	// 読み込んでいないものとして処理
	int handle = LoadGraph(name.c_str());
	ImageData data;
	data.fileName = name;
	data.handle = handle;
	m_images.emplace_back(data);
	return handle;
}
