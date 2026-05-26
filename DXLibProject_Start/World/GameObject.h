#pragma once
#include<memory>
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../World/Component/Collision.h"
/// <summary>
/// ゲームで扱うオブジェクトの基本クラス
/// 座標・モデル・衝突判定・ライフサイクルを管理する
/// アニメーションを持ったオブジェクトを作る際は、別途対応が必要
/// </summary>
class GameObject
{
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
	virtual void Update() = 0;
	virtual void Draw();

	/// <summary>
	/// トランスフォームを取得
	/// </summary>
	/// <returns></returns>
	const Transform& GetTransform()const { return m_transform; }
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return m_transform.position; }
	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns></returns>
	const Collision::Shape& GetCollision()const { return *m_collision; }
	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="result"></param>
	virtual void ResolveCollision(const Collision::Result& result) = 0;
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
	int m_modelHandle;

	/// <summary>
	/// 当たり判定
	/// ポリモーフィズムで異なる形状をクラスごとに持つ
	/// nullptrにしたら持たないことも選択できる(積極的には使用しない)
	/// </summary>
	std::unique_ptr<Collision::Shape>m_collision;

};

