#pragma once
#include"../../GameObject.h"
#include"../Character.h"
#include"../AnimationController.h"
#include"../CharacterMove.h"
#include"DragonAttack.h"
#include"../../UI/Gauge.h"
#include"../../UI/GaugeShow.h"
#include"../../../Utility/Input.h"
#include<array>
namespace {
	enum FollowState {
		Normal,
		Attack,
		RouteSearch
	};
	constexpr int kBleathCount = 30;
}
class Player;
class GameObjectManager;
class SquareData;
class DragonAttack;
class DragonBreath;
class ManhattanMoveData;
class Dragon:public Character
{
public:
	Dragon();
	~Dragon();

	void Init()override;
	void Update(float deltaTime)override;
	const Character::Type& GetCharacterType()override { return Character::Type::Dragon; }
	void UpdateFromInput();
	/// <summary>
	/// 追従時の更新処理
	/// </summary>
	void FollowUpdate(float deltaTime);
	/// <summary>
	/// 攻撃時の更新処理　
	/// </summary>
	void AttackUpdate(float deltaTime);
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	/// <summary>
	/// ターゲットを追いかける処理
	/// </summary>
	void Call();
	/// <summary>
	/// マスターの元へ戻る
	/// </summary>
	void CallBack();
	/// <summary>
	/// マスターを設定
	/// </summary>
	void SetMaster(GameObject* pMaster) { m_pMaster = pMaster; }
	Vector3 CheckFollowOffset();
	void SetPosition(const Vector3& pos)override;
	void SetPad(Input::Pad pad) { m_pad = pad; }
	void SetTarget(GameObject* target) { m_pTarget = target; }
private:
	void FollowPlayer();
	void FollowTarget(float deltaTime);
	void FollowRoute();

	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	void UpdateAnimation(float deltaTime);
	/// <summary>
	/// アニメーションの変更を行う処理
	/// </summary>
	void ChangeAnimation(const Status::Dragon& status);

	void Breath();
	void CheckRouteManhattan();
	bool CanMoveManhattan(SquareData* square);
	/// <summary>
	/// 経路探索で通行可能かつ指定した座標から最短距離のマスIDを取得
	/// </summary>
	int GetNearestCanMoveTile(const Vector3& position);
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimationController m_animation;
	/// <summary>
	/// アニメーションデータの配列
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Dragon::Max)] = { -1 };
	/// <summary>
	/// 現在のステータス
	/// </summary>
	Status::Dragon m_status;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Dragon::Max)];
	GameObject* m_pTarget;
	GameObject* m_pMaster;
	FollowState m_followState;
	CharacterMove m_move;
	DragonAttack m_attack;
	bool m_attackFlag;
	bool m_canAttackFlag;
	float m_speed;

	std::array<DragonBreath*, kBleathCount> m_breath;

	Input::Pad m_pad;
	std::vector<ManhattanMoveData> moveData;
	int m_routeSearchTileID;
	int m_routeSearchPlayerTileID;
};

