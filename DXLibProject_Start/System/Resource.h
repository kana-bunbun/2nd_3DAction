#pragma once
#include<string>
#include<vector>
class Resource {
public:
	Resource() = default;
	~Resource() = default;
public:
	int GetHandle() { return m_handle; }
	std::string GetName() { return m_name; }
private:
	virtual void Load(std::string path) = 0;
	virtual void Delete() = 0;
protected:
	int m_handle;			// データのハンドル
	std::string m_name;	// データ名
};

class ModelData :public Resource {			// モデルのデータ
public:
	ModelData(std::string path);
	~ModelData();
	ModelData* Duplicate();
public:
	const std::vector<int>& GetAnimHandle()const { return m_animHandle; }
private:
	void Load(std::string path)override;
	void Delete()override;
private:
	std::vector<int> m_animHandle;
};
class GraphData :public Resource {			// 画像のデータ
public:
	GraphData(std::string path);
	~GraphData();
private:
	void Load(std::string path)override;
	void Delete()override;
};