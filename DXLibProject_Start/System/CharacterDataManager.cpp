#include "pch.h"
#include "CharacterDataManager.h"
#include "Data/CharacterData.h"
#include "Utility/Loader/CsvLoader.h"

namespace {
	const char* const kFilePath = "CharacterData";
}

CharacterDataManager& CharacterDataManager::GetInstance()
{
	static CharacterDataManager instance;
	return instance;
}
CharacterDataManager::CharacterDataManager():
	m_characterDataList()
{
	m_characterDataList.clear();
	Load();
}

const CharacterData& CharacterDataManager::GetCharacterData(int id)
{
	for (auto& characterData : m_characterDataList) {
		if (characterData.ID != id)continue;

		return characterData;
	}
	assert(false && "GetCharacterData not found id");
	return CharacterData();
}

void CharacterDataManager::Load()
{
	m_characterDataList = Data::Csv::LoadCsvAs<CharacterData>(kFilePath);
}

