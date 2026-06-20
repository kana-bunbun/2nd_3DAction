#pragma once
#include"../GameObject.h"
/// <summary>
/// 階段オブジェクトの処理を行う
/// </summary>
class Stair:public GameObject
{
	Stair();
	~Stair();

	void Init()override;
	void Update(float deltaTime)override;
	void ResolveCollision(GameObject& other, const Collision::Result& result);

	/// <summary>
	/// 自身の座標を指定したタイルの座標に設定する
	/// </summary>
	/// <param name="tileID">タイルのID</param>
	void SetTile(int tileID);

};

