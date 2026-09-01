#pragma once
#include<memory>
#include<vector>
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../World/Component/Collision.h"
#include"GameObjectParam.h"
#include"../System/Resource.h"
#include"Input/InputData.h"
/// <summary>
/// ゲームで扱うオブジェクトの基本クラス
/// 座標・モデル・衝突判定・ライフサイクルを管理する
/// アニメーションを持ったオブジェクトを作る際は、別途対応が必要
/// </summary>
class GameObject
{
public:
	struct CollisionData {
	public:
		std::unique_ptr<Collision::Shape>shape;
		CollisionType type;
	};
	struct HitCollisionData {
	public:
		Collision::Shape* collision;
		bool isHit;
	};
public:
	GameObject();
	virtual ~GameObject() = default;

	/// <summary>
	/// デストラクタ・コンストラクタとInit関数、End関数を区別
	/// Init・End関数はゲーム的な終了・開始処理
	/// コンストラクタ・デストラクタはC++オブジェクトとしての後処理等をする際
	/// Init・End関数はマネージャー経由等で呼ぶ
	/// メンバの解放やゲーム使用上の後処理で行う
	/// デストラクタはメモリの開放、ポインタの後処理、破棄忘れを防ぐ
	/// </summary>

	virtual void Init() = 0;
	virtual void End();
	virtual void Update(float deltaTime, const InputData& inputData) {};
	virtual void UpdateCollision();
	virtual void LateUpdate(float deltaTime) {};	// 最後に行いたい更新処理
	virtual void Draw();
	virtual void LateDraw() {};	// 最後に行いたい描画処理
	virtual void DebugCollision(int color=Color::kWhite);
	virtual void Damage(float damage){}
	virtual void Heal(float heal) {}
	/// <summary>
	/// トランスフォームを取得
	/// 値変更をしてほしくないため最初にconst
	/// m_transformを変更してほしくないため最後にconst
	/// </summary>
	/// <returns></returns>
	const Transform& GetTransform()const { return m_transform; }
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return m_transform.position; }
	virtual void SetPosition(const Vector3& position);
	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns></returns>
	//const Collision::Shape& GetCollision()const { return *m_collision; }
	//const Collision::Shape& GetCollision()const;
	const std::vector<CollisionData>&GetCollisions()const { return m_collisions; }
	const CollisionTag& GetCollisionTag()const { return m_collisionTag; }
	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="result"></param>
	virtual void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
		) = 0;
	void UpdateHitData();
	/// <summary>
	/// コリジョンの追加
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="type"></param>
	void AddCollision(std::unique_ptr<Collision::Shape> shape,CollisionType type);
	/*void AddCollision(const AddCollisionAABBData& addCollisionData);
	void AddCollision(const AddCollisionSphereData& addCollisionData);*/

	/// <summary>
	/// 現在いるマスのIDを取得
	/// </summary>
	int GetOnTileID();

	bool IsActive()const { return m_isActive; }
	void SetActive(const bool active) { m_isActive = active; }
	/// <summary>
	/// モデルを透明・半透明にして描画するかどうか
	/// 派生先のオブジェクトによって是非が変わる
	/// </summary>
	/// <returns></returns>
	virtual bool IsTransparent() { return false; }
	virtual bool IsDead() { return false; }
protected:
	bool IsCollisionEnter(Collision::Shape* collision);

	
protected:
	/// <summary>
	/// 座標・回転・拡縮
	/// クラス内でしか使用しない
	/// GameObjectクラスのインスタンスは絶対に持っている情報なので
	/// 値オブジェクトとして宣言
	/// </summary>
	Transform m_transform;

	/// <summary>
	/// モデルハンドル
	/// </summary>
	ModelData* m_modelData;

	/// <summary>
	/// 当たり判定
	/// ポリモーフィズムで異なる形状をクラスごとに持つ
	/// nullptrにしたら持たないことも選択できる(積極的には使用しない)
	/// </summary>
	std::vector<CollisionData>m_collisions;
	/// <summary>
	/// 衝突時のオブジェクトの属性
	/// </summary>
	CollisionTag m_collisionTag = CollisionTag::None;

	/// <summary>
	/// アクティブかどうか
	/// </summary>
	bool m_isActive=true;

	/// <summary>
	/// 現在いるマスのID
	/// </summary>
	int m_onTileID;
	/// <summary>
	/// 前回当たり判定チェック時の座標
	/// </summary>
	Vector3 m_oldPos;
	/// <summary>
	/// 当たり判定の接触ログ
	/// </summary>
	std::vector<GameObject::HitCollisionData> m_hitData;

};

