#pragma once
#include"pch.h"

struct CharacterData;
class CharacterDataManager
{
public:

	static CharacterDataManager& GetInstance();

	const CharacterData& GetCharacterData(int id);

	void Load();

private:
	CharacterDataManager();
	CharacterDataManager(const CharacterDataManager&) = delete;
	CharacterDataManager& operator =(const CharacterDataManager&) = delete;
	CharacterDataManager(CharacterDataManager&&) = delete;
	CharacterDataManager& operator =(const CharacterDataManager&&) = delete;
private:

	std::vector<CharacterData>m_characterDataList;

};

