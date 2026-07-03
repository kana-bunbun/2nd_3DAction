#pragma once
#include<memory>
#include<vector>
#include"../GameObject.h"
#include"../GameObjectManager.h"
#include"../../Utility/Input.h"
class Character;
class Player;
class Dragon;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	void Init();
	void SetRandomPos();
	void SetPad(Input::Pad pad);

public:
	void SetGameObjectManager(GameObjectManager* pGameObjectManager) { m_pGameObjectManager = pGameObjectManager; }
private:
	// GameObjectのマネージャー
	GameObjectManager* m_pGameObjectManager;
	// キャラクターの配列
	std::vector<Character*> m_characters;
	// プレイヤーのポインタ
	Player* m_pPlayer;
	// ドラゴンのポインタ
	Dragon* m_pDragon;
};
