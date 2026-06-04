#pragma once
#include"../../GameObject.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
#include"DragonAttack.h"
#include"../../UI/Gauge.h"
#include"../../UI/GaugeShow.h"
namespace {
	enum FollowState {
		Normal,
		Attack
	};
}
class Player;
class DragonAttack;
class Dragon:public GameObject
{
public:
	Dragon();
	~Dragon();

	void Init()override;
	void Update()override;
	/// <summary>
	/// 追従時の更新処理
	/// </summary>
	void FollowUpdate();
	/// <summary>
	/// 攻撃時の更新処理　
	/// </summary>
	void AttackUpdate();
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;
	/// <summary>
	/// ターゲットを設定して追いかける処理
	/// </summary>
	/// <param name="target"></param>
	void Call(GameObject* target);
	void CallBack();
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	Vector3 CheckFollowOffset();
	Gauge* GetGauge() { return m_gauge.get(); }

private:
	void FollowPlayer();
	void FollowTarget();

	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	void UpdateAnimation();
	/// <summary>
	/// アニメーションの変更を行う処理
	/// </summary>
	void ChangeAnimation(const Status::Dragon& status);

private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimatioController m_animation;
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
	std::unique_ptr<Gauge> m_gauge;
};

