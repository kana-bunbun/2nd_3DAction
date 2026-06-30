#pragma once
#include<array>
#include<vector>
#include<string>
class BlendManager {
public:
	enum class Type {
		Invalid = -1,
		Apple,
		Beer,
		Bread,
		Cheese,
		CheeseBread,
		Max,
	};

	static BlendManager& GetInstnce();
	void Init();
public:
	~BlendManager();
	const BlendManager::Type& Blend(const BlendManager::Type& base, const BlendManager::Type& add);
	void Debug();
private:
	void LoadRecipe( std::vector<std::vector<std::string>> loadData);
	BlendManager::Type SToItemType(std::string name);
	std::string ItemTypeToS(const BlendManager::Type& type)const;
private:
	BlendManager()=default;
	BlendManager(const BlendManager&)=delete;
	BlendManager& operator=(const BlendManager&) = delete;
	BlendManager(BlendManager&&) = delete;
	BlendManager& operator=(const BlendManager&&) = delete;
private:
	std::array <std::array<int, static_cast<int>(BlendManager::Type::Max)>, static_cast<int>(BlendManager::Type::Max)> ItemRecipe;
};