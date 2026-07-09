#pragma once
#include<memory>
#include<vector>
#include"../GameObject.h"
#include"../GameObjectManager.h"
#include"../../Utility/Input.h"
#include"../Character/Character.h"
class Player;
class Dragon;
class CharacterManager
{
public:
	static CharacterManager& GetInstance();

	~CharacterManager();
	void Init();
	void SetRandomPos();
	void SetPad(Input::Pad pad);
	Character* GetCharacter(int ID);
	Player* GetPlayer();
	
public:
	/// <summary>
	/// 指定した種類のキャラクターを返す処理
	/// </summary>
	Character* CheckNearestCharacter(const Vector3& basePosition,const Character::Type& characterType = Character::Type::Invalid);
private:
	CharacterManager() = default;
	CharacterManager& operator=(const CharacterManager&) = delete;
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager& operator=(CharacterManager&&) = delete;
	CharacterManager(const CharacterManager&&) = delete;
private:
	// キャラクターの配列
	std::vector<Character*> m_characters;
	// プレイヤーのポインタ
	Player* m_pPlayer;
	// ドラゴンのポインタ
	Dragon* m_pDragon;
};
