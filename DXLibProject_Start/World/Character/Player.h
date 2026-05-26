#include"../GameObject.h"
#include"AnimatioController.h"

class Camera;

class Player : public GameObject 
{
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	void Update()override;
	void ResolveCollision(const Collision::Result& result)override;
	/// <summary>
	/// カメラのポインタを渡す関数
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(Camera* camera) { m_pCamera = camera; }
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
	Status::Player m_status;
	/// <summary>
	/// カメラのポインタ
	/// </summary>
	Camera* m_pCamera;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Player::Max)];

	/// <summary>
	/// プレイヤーの角度
	/// </summary>
	float m_desireRad;

};
