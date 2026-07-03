#include "CharacterManager.h"
#include "Character.h"
#include "Guardian/Dragon.h"
#include "Player/Player.h"
#include "../Map/MapCreate.h"
#include "../Map/MapManager.h"
#include "../../Utility/MyRandom.h"
CharacterManager::CharacterManager():
	m_pGameObjectManager(nullptr),
	m_characters(),
	m_pPlayer(nullptr),
	m_pDragon(nullptr)
{
	m_characters.clear();
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
	m_characters = m_pGameObjectManager->FindObjects<Character>();
	// 部屋マスのIDの配列を取得
	std::vector<int>rooms = MapCreate::GetInstance().GetRooms();

	m_pDragon = m_pGameObjectManager->FindObject<Dragon>();
	m_pPlayer = m_pGameObjectManager->FindObject<Player>();
	Vector3 playerPos = Vector3::zero;
	for (auto& character : m_characters) {
		// 部屋マスの配列のインデックスをランダムで取得
		int roomID = MyRandom::Int(0, rooms.size()-1);
		// ランダムで取得した値のIDをもとにマスのワールド座標を取得
		Vector3 randomPos = MapManager::GetInstance().GetWorldPosFromID(rooms[roomID]);
		// 取得したワールド座標にキャラクターを配置
		character->SetPosition(randomPos);
		// 指定したインデックスの要素を削除
		rooms.erase(rooms.begin() + roomID);

		// プレイヤーの場合、生成座標を保持しておく
		if (character!=m_pPlayer)continue;
		playerPos = randomPos;
	}
	m_pDragon->SetPosition(playerPos);
}

void CharacterManager::SetPad(Input::Pad pad)
{
	if (m_pPlayer)
		m_pPlayer->SetPad(pad);
}
