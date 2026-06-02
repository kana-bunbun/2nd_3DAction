#pragma once
#include"../../GameObject.h"
#include"../AnimatioController.h"
class Dragon:public GameObject
{
public:
	Dragon();
	~Dragon();

	void Init()override;
	void Update()override;
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;
	void Call(const Vector3& target);
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimatioController m_animation;
	/// <summary>
	/// アニメーションデータの配列
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Player::Max)] = { -1 };
	/// <summary>
	/// 現在のステータス
	/// </summary>
	Status::Dragon m_status;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Player::Max)];
};

