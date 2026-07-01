#pragma once
#include<memory>
#include<vector>
#include"../GameObject.h"
#include"../GameObjectManager.h"
class Character;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	void Init();
	void SetRandomPos();

public:
	void SetGameObjectManager(GameObjectManager* pGameObjectManager) { m_pGameObjectManager = pGameObjectManager; }
	//const std::vector<Character*> GetCharacters() { return m_characters; }
private:
	// GameObjectのマネージャー
	GameObjectManager* m_pGameObjectManager;
	// キャラクターの配列
	std::vector<Character*> m_characters;
};
