#pragma once
#include<memory>
#include<vector>
#include<type_traits>
#include"../GameObject.h"
#include"../GameObjectManager.h"

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	void Init();
	void SetRandomPos();
	// キャラクターを生成する関数
	template <class T, class... Args>
	T* CreateCharacter(Args&&... args);

public:
	void SetGameObjectManager(GameObjectManager* pGameObjectManager) { m_pGameObjectManager = pGameObjectManager; }
	const std::vector<GameObject*> GetCharacters() { return m_characters; }
private:
	// GameObjectのマネージャー
	GameObjectManager* m_pGameObjectManager;
	// キャラクターの配列
	std::vector<GameObject*> m_characters;
};

template<class T, class ...Args>
inline T* CharacterManager::CreateCharacter(Args && ...args)
{
	if (!m_pGameObjectManager)return nullptr;
	// GameObjectクラスを継承しているかどうか判定
	static_assert(std::is_base_of<GameObject, T>::value, "キャラクター生成:対象がGameObjectを未継承");
	// オブジェクト生成
	T* character = m_pGameObjectManager->CreateObject(args);

	// 初期化
	character->Init();

	// m_charactersに登録
	m_characters.push_back(character);
	return character;
}

