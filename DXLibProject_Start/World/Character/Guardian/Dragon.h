#pragma once
#include"../../GameObject.h"
#include"../AnimationController.h"
#include"../CharacterMove.h"
#include"DragonAttack.h"
#include"../../UI/Gauge.h"
#include"../../UI/GaugeShow.h"
#include<array>
namespace {
	enum FollowState {
		Normal,
		Attack
	};
	constexpr int kBleathCount = 30;
}
class Player;
class DragonAttack;
class DragonBreath;
class Dragon:public GameObject
{
public:
	Dragon();
	~Dragon();

	void Init()override;
	void Update(float deltaTime)override;
	/// <summary>
	/// 追従時の更新処理
	/// </summary>
	void FollowUpdate(float deltaTime);
	/// <summary>
	/// 攻撃時の更新処理　
	/// </summary>
	void AttackUpdate(float deltaTime);
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;
	void ResolveCollision(GameObject::CollisionTag tag, const Collision::Result& result)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	/// <summary>
	/// ターゲットを設定して追いかける処理
	/// </summary>
	/// <param name="target"></param>
	void Call(GameObject* target);
	void CallBack();
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	Vector3 CheckFollowOffset();
	std::shared_ptr<Gauge> GetGauge() { return m_gauge; }

private:
	void FollowPlayer();
	void FollowTarget(float deltaTime);

	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	void UpdateAnimation(float deltaTime);
	/// <summary>
	/// アニメーションの変更を行う処理
	/// </summary>
	void ChangeAnimation(const Status::Dragon& status);

	void Breath();
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
	Player* m_pPlayer;
	FollowState m_followState;
	CharacterMove m_move;
	DragonAttack m_attack;
	bool m_attackFlag;
	bool m_canAttackFlag;
	float m_speed;
	std::shared_ptr<Gauge> m_gauge;

	std::array<std::unique_ptr<DragonBreath>, kBleathCount> m_breath;

};

