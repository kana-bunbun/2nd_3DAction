#include"../../GameObject.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
#include"../../UI/Gauge.h"
#include"../../UI/GaugeShow.h"
#include<array>
class CameraOld;
class Barrier;


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
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// ステータスに応じた行動の更新処理
	/// </summary>
	void UpdateAction();
	/// <summary>
	/// はじき返しの処理
	/// </summary>
	void Parry();
	/// <summary>
	/// フラグ管理の処理
	/// </summary>
	void UpdateFlag();
	/// <summary>
	/// トランスフォームの更新処理
	/// </summary>
	void UpdateTransform();
	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	void UpdateAnimation();
	/// <summary>
	/// アニメーションの変更を行う処理
	/// </summary>
	void ChangeAnimation(Status::Player& status);
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="result"></param>
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;



public:
	Vector3 GetCollisionCenterPos();
	/// <summary>
	/// カメラのポインタを渡す関数
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(CameraOld* camera) { m_pCamera = camera; }
	void SetBarrier(Barrier* barrier);
	Gauge* GetGauge(int num) { return m_gauges[num].get(); }
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
	CameraOld* m_pCamera;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Player::Max)];
	/// <summary>
	/// 移動速度
	/// </summary>
	float m_speed;
	/// <summary>
	/// プレイヤーの角度
	/// </summary>
	float m_desireRad;
	/// <summary>
	/// キャラクターの移動を行う
	/// </summary>
	CharacterMove m_move;
	/// <summary>
	/// パリィを行ったかどうか
	/// </summary>
	bool m_parry;
	/// <summary>
	/// バリア
	/// </summary>
	Barrier* m_pBarrier;
	/// <summary>
	/// ダッシュしているかどうか
	/// </summary>
	bool m_dashFlag;
	/// <summary>
	/// ゲージの種類
	/// </summary>
	std::array<std::unique_ptr<Gauge>, static_cast<int>(GaugeType::Max)> m_gauges;
	public:
	Collision::Capsule m_capsule;
};
