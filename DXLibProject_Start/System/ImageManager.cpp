#include "ImageManager.h"
#include"ImageResource.h"
#include"../Utility/Loder/CsvLoader.h"
#include"../Data/GraphPathParam.h"
#include<DxLib.h>
#include<cassert>
namespace{
	const char* const kGraphPath = "Resource\\Graph\\";
	const char* const kPng = ".png";
	const char* const kDataName = "GraphPathParam";
}
ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}
ImageManager::ImageManager()
{
	Load();
}


void ImageManager::Init()
{

}

void ImageManager::End()
{
	m_images.clear();
}

void ImageManager::Load()
{
	m_graphPathParam = Data::Csv::LoadCsvAs<GraphPathParam>(kDataName);
}

std::shared_ptr<ImageResource> ImageManager::GetImage(int ID)
{
	// 同じデータを読み込んでいないかどうかチェック
	for (const auto& image : m_images) {
		if (image->GetID()!= ID)continue;
		return image;
	}

	// ハンドル作成に失敗していないかどうかチェック

	// 読み込んでいないものとして処理
	std::string path = kGraphPath + GetGraphPath(ID) + kPng;
	int handle = LoadGraph((path).c_str());
	assert(handle != -1, "ImageManager : GetGraphHandle handle==-1");
	if (handle == -1)return nullptr;
	std::shared_ptr<ImageResource>image = std::make_shared<ImageResource>(ID, handle);
	m_images.emplace_back(image);
	return image;
}

const std::string& ImageManager::GetGraphPath(int ID)
{
	for (auto& param : m_graphPathParam) {
		if (param.ID != ID)continue;
		return param.graphName;
	}
	return "";
}

bool ImageManager::Exists(int ID) const
{
	for (const auto& image : m_images) {
		// ファイルパスが同じものを探す
		if (image->GetID() != ID)continue;
		// あればtrue
		return true;
	}
	return false;
}

bool ImageManager::IsLodad(int ID) const
{
	for (const auto& image : m_images) {
		// ファイルパスが同じものを探す
		if (image->GetID() != ID)continue;
		// あれば読み込めているかどうかチェック
		return image->GetHandle() != -1;
	}
	return false;
}

bool ImageManager::ReleaseGraph(int ID)
{

	for (auto it = m_images.begin(); it != m_images.end(); ++it) {
		// 指定したパスの画像を管理しているかどうかチェック
		if (it->get()->GetID()!= ID)continue;
		if (it->get()->GetHandle() != -1) {
			DeleteGraph(it->get()->GetHandle());
		}
		m_images.erase(it);
		return true;
	}
	return false;
}

