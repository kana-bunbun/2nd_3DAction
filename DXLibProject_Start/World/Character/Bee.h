#pragma once
#include"../GameObject.h"
#include"../Character/AnimationController.h"
#include"../../Utility/Vector3.h"
class Bee:public GameObject
{
public:
	Bee();
	~Bee()override = default;

	/// <summary>
	/// GameObjectクラスのメンバ関数
	/// </summary>
	void Init()override;
	void Update(float deltaTime)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	/// <summary>
	/// Beeクラスのメンバ変数
	/// </summary>
	/// <returns></returns>
	Vector3 GetCollisionCenterPos()const;
	void UpdateAnimation(float deltaTime);
	void ChangeAnimation(Status::Bee next);
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimationController m_animation;
	/// <summary>
	/// 再生中のアニメーション
	/// </summary>
	Status::Bee m_state;
	/// <summary>
	/// アニメーションデータの番号
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Bee::Max)] = { -1 };

};

