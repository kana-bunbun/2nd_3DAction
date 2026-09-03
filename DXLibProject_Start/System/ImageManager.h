#pragma once
#include<string>
#include<vector>
#include<memory>
#include"ImageResource.h"
struct GraphPathParam;
class ImageResource;
class ImageManager
{
public:

public:
	static ImageManager& GetInstance();
	~ImageManager() = default;
	void Init();
	void End();
	void Load();
	// 画像ハンドルの取得
	std::shared_ptr<ImageResource> GetImage(int ID);
	const std::string& GetGraphPath(int ID);
	// 現在何を読み込んでいるのか
	// 正常に読み込んでいるのか
	// 読み込んだものを解放できるのか
	
	/// <summary>
	/// 現在読み込んでいる画像の個数を返す
	/// </summary>
	/// <returns></returns>
	int GetLoadedCount()const {return m_images.size(); }
	/// <summary>
	/// 指定したパスの画像が管理されているかどうかチェック
	/// 主にデバッグ目的で使用することを想定
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	bool Exists(int ID)const;
	/// <summary>
	/// 指定したパスの画像が正常にロードされているかどうかチェック
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	bool IsLodad(int ID)const;
	/// <summary>
	/// 指定したパスの画像を破棄
	/// 必要に応じて個別で解放できるようにする
	/// 不要な画像を破棄してメモリの使用状態の無駄をなくすことが目的
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	bool ReleaseGraph(int ID);
private:
	ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	ImageManager(ImageManager&&) = delete;
	ImageManager& operator=(const ImageManager&&) = delete;
private:
	/// <summary>
	/// 管理している画像データ
	/// </summary>
	std::vector<std::shared_ptr<ImageResource>>m_images;
	std::vector<GraphPathParam>m_graphPathParam;

};

