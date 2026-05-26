#pragma once
#include"../GameObject.h"
#include"AnimatioController.h"
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
	void Update()override;
	void ResolveCollision(const Collision::Result& result)override;
	/// <summary>
	/// Beeクラスのメンバ変数
	/// </summary>
	/// <returns></returns>
	Vector3 GetCollisionCenterPos()const;
	void UpdateAnimation();
	void ChangeAnimation(Status::Bee next);
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimatioController m_animation;
	/// <summary>
	/// 再生中のアニメーション
	/// </summary>
	Status::Bee m_state;
	/// <summary>
	/// アニメーションデータの番号
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Bee::Max)] = { -1 };

};

