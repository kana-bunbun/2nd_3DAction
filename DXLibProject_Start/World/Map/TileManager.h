#pragma once
#include"../Component/Transform.h"
#include"../../Utility/Vector3.h"
#include"../../Utility/Input.h"
#include"../GameObject.h"
#include<memory>
#include<vector>
class TileObject;
class Stair;
class Player;
class EnemyManager;
class TileManager
{
public:
	TileManager();
	~TileManager();

	void SetUpFloor();
	void Update(float deltaTime);
	void Draw();
	void DrawMiniMap();
	bool InDevideList(size_t id);
	void DrawMark();
	void SetMarkPos(Transform markPos) { m_markPos = markPos; }

	int RandomPassableID();
	int RandomRoomID();
	Collision::Result CheckCollision(GameObject* object);
public:
	void SetEnemyManager(EnemyManager* pEnemyManager) { m_pEnemyManager = pEnemyManager; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetPad(Input::Pad pad) { m_pad = pad; }
	bool IsUpStair() { return m_upStair; }
	TileObject* GetObj() { return m_pTiles[0].get(); }
private:
	Transform m_markPos;
	int m_cursorHandle;
	std::vector<std::unique_ptr<TileObject>> m_pTiles;
	int m_floorHandle;
	int m_wallHandle;
	std::unique_ptr<Stair>stair;
	// 階段を登れるかどうか
	bool m_upStair;
	int m_stairID;
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	Input::Pad m_pad;
};

