#include "CharacterManager.h"
#include "Character.h"
#include "Guardian/Dragon.h"
#include "Player/Player.h"
#include "../Map/MapCreate.h"
#include "../Map/MapManager.h"
#include "../../Utility/MyRandom.h"
CharacterManager& CharacterManager::GetInstance()
{
	static CharacterManager instance;
	return instance;
}
CharacterManager::~CharacterManager()
{

}

void CharacterManager::Init()
{

}

void CharacterManager::SetRandomPos()
{
	//m_characters.clear();
	// キャラクターの配列を取得
	m_characters = GameObjectManager::GetInstance().GetCharacters();
	// 部屋マスのIDの配列を取得
	std::vector<int>rooms = MapCreate::GetInstance().GetRooms();

	// ドラゴンのポインタがなければ取得
	if(!m_pDragon)
	m_pDragon = GameObjectManager::GetInstance().FindObject<Dragon>();
	// プレイヤーのポインタがなければ取得
	if(!m_pPlayer)
	m_pPlayer = GameObjectManager::GetInstance().FindObject<Player>();
	// プレイヤー座標を格納する変数
	Vector3 playerPos = Vector3::zero;

	for (auto& character : m_characters) {
		if (!rooms.size())break;
		// 部屋マスの配列のインデックスをランダムで取得
		int roomID = MyRandom::Int(0, rooms.size()-1);
		// ランダムで取得した値のIDをもとにマスのワールド座標を取得
		Vector3 randomPos = MapManager::GetInstance().GetWorldPosFromID(rooms[roomID]);
		// 取得したワールド座標にキャラクターを配置
		character->SetPosition(randomPos);
		character->Setup();
		// 指定したインデックスの要素を削除
		rooms.erase(rooms.begin() + roomID);

		// キャラクターがプレイヤーの場合、生成座標を保持しておく
		if (character!=m_pPlayer)continue;
		playerPos = randomPos;

	}
	// ドラゴンの座標にプレイヤー座標を設定しておく
	m_pDragon->SetPosition(playerPos);
}

void CharacterManager::SetPad(Input::Pad pad)
{
	if (m_pPlayer)
		m_pPlayer->SetPad(pad);
}

Character* CharacterManager::GetCharacter(int ID)
{
	// 配列に対して有効な値かどうかをチェック
	if (ID >= 0 && ID < m_characters.size()) {
		// 有効な値なら指定したIDのキャラクターを返す
		return m_characters[ID];
	}
	// 有効な値でないときnullptr
	return nullptr;
}

Player* CharacterManager::GetPlayer()
{
	// プレイヤーのポインタがないとき
	if (!m_pPlayer) {
		// キャラクターの配列を総当たりして調べる
		for (auto& character : m_characters) {
			// キャラクターの種類がプレイヤーでないときreturn
			if (character->GetCharacterType() != Character::Type::Player)continue;
			// キャストしてプレイヤークラスでなければスルー
			Player* player = dynamic_cast<Player*>(character);
			if (!player)continue;
			// プレイヤーなら
			m_pPlayer = player;
			// ループを抜ける
			break;
		}
	}
	// ポインタを返す
	return m_pPlayer;
}

Dragon* CharacterManager::GetDragon()
{
	// ドラゴンのポインタがないとき
	if (!m_pDragon) {
		// キャラクターの配列を総当たりして調べる
		for (auto& character : m_characters) {
			// キャラクターの種類がプレイヤーでないときreturn
			if (character->GetCharacterType() != Character::Type::Dragon)continue;
			// キャストしてドラゴンでなければスルー
			Dragon* dragon = dynamic_cast<Dragon*>(character);
			if (!dragon)continue;
			// ドラゴンなら
			m_pDragon = dragon;
			// ループを抜ける
			break;
		}
	}
	// ポインタを返す
	return m_pDragon;
}


// 指定したキャラクターが不正値ならすべてのキャラクターの中で最も近いキャラクターを返す
Character* CharacterManager::CheckNearestCharacter(const Vector3& basePosition, const Character::Type& characterType)
{
	Character* character = nullptr;
	// GameObjectManagerの配列と要素数が異なるとき
	std::vector<Character*>characters= GameObjectManager::GetInstance().GetCharacters();
	m_characters = characters;
	// 最短距離を格納する変数を不正値で初期化
	float minLength = -1;
	for (int i = 0; i < m_characters.size(); i++) {
		// nullptrまたはアクティブでないキャラクターはスルー
		if (!m_characters[i]||!m_characters[i]->IsActive())continue;
		// キャラクターの種類が指定されている時、かつ指定した種類のキャラクターでなければスルー
		if (characterType != Character::Type::Invalid &&
			m_characters[i]->GetCharacterType() != characterType)continue;
		// 死亡しているキャラクターはスルー
		if (!m_characters[i]->GetHP()->GetValue())continue;
		// 距離の差を取得
		Vector3 differ = (basePosition - m_characters[i]->GetTransform().position);
		differ.y = 0;
		// キャラクターとの距離を計算
		float characterLength = differ.GetSqLength();
		// minLengthに正常値が入っているときかつ、
		// 調べた距離が最短距離でないときスルー
		if (minLength > 0 && minLength < characterLength)continue;
		// 最短距離なら

		// 最短距離の更新
		minLength = characterLength;
		// 返す値の更新
		character = m_characters[i];
	}
	// 最短距離のキャラクターのポインタを返す
	return character;
}
