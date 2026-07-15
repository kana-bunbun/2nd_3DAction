#pragma once
#include<array>
#include<vector>
#include<string>
#include"ItemData.h"
#include"BlendRecipe.h"
class BlendManager {
public:

	static BlendManager& GetInstnce();
	void Init();
public:
	~BlendManager();
	const ItemData::Type& Blend(const ItemData::Type& base, const ItemData::Type& add);
	void Debug();
private:
private:
	BlendManager()=default;
	BlendManager(const BlendManager&)=delete;
	BlendManager& operator=(const BlendManager&) = delete;
	BlendManager(BlendManager&&) = delete;
	BlendManager& operator=(const BlendManager&&) = delete;
private:
	std::vector <BlendRecipe> m_itemRecipe;
};