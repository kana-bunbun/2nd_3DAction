#pragma once
#include"../GameObject.h"
class Barrier:public GameObject
{
public:
	Barrier(const Vector3& offset=Vector3::zero);
	~Barrier();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="result"></param>
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;
	/// <summary>
	/// 透明度の計算をする関数
	/// </summary>
	/// <returns></returns>
	float CheckAlpha();
public:
	/// <summary>
	/// 座標を設定する関数
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) { m_transform.position = position + m_offset; }
	/// <summary>
	/// 透明度が変化する速さを設定
	/// </summary>
	/// <param name="speed"></param>
	void SetSpeed(float speed) { m_speed = speed; }
	void SetOffset(const Vector3& offset) { m_offset = offset; }
private:
	/// <summary>
	/// 描画の透明度
	/// </summary>
	float m_alpha;
	/// <summary>
	/// 経過時間
	/// </summary>
	float m_time;
	/// <summary>
	/// 値が変わる速さの倍率
	/// </summary>
	float m_speed;
	/// <summary>
	/// オフセット位置
	/// </summary>
	Vector3 m_offset;
};

