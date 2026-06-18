#pragma once
#include<memory>
#include<vector>
#include<type_traits>
#include"GameObject.h"
/// <summary>
/// GameObjectの生成・更新・衝突判定・破棄を一括で管理するクラス
/// </summary>
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Init();
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	void Update(float deltaTime);		
	/// <summary>
	/// 最後に処理をしたい更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	void LateUpdate(float deltaTime);	
	void Draw();
	/// <summary>
	/// 当たり判定処理
	/// </summary>
	void CheckCollision();			

	/// <summary>
	/// 管理している全オブジェクトの終了処理
	/// </summary>
	void Clear();
	/// <summary>
	/// オブジェクトの削除予約
	/// </summary>
	/// <param name="obj"></param>
	void DestroObject(GameObject* obj);
	/// <summary>
	/// 削除予約されたオブジェクトの全削除
	/// </summary>
	void ProcessDestroy();

	const std::vector<std::unique_ptr<GameObject>>& GetObjects()const;

	template <class T,class... Args>
	T* CreateObject(Args&&... args);

private:
	// 管理中のオブジェクト
	std::vector<std::unique_ptr<GameObject>>m_objects;
	// 削除予定のオブジェクト
	std::vector<GameObject*>m_destrpyObjects;
};

template<class T, class ...Args>
inline T* GameObjectManager::CreateObject(Args && ...args)
{
	// GameObjectクラスを継承しているかどうか判定
	//static_assert(std::is_base_of<GameObject, T>::value, "GameObjectクラスを継承していない");
	static_assert(std::is_base_of<GameObject, T>::value,"GameObjectクラス");
	// オブジェクト生成
	auto obj = std::make_unique<T>(std::forward<Args>(args)...);

	// 初期化
	obj->Init();

	// GameObjectManagerクラスがオブジェクトを所有する
	// 外部参照用の生ポインタrawPtrを取得
	// 所有権を1つにしたいのでshared_ptrではなくunique_ptrで保持
	T* rawPtr = obj.get();

	// スマートポインタをm_objectsに登録
	m_objects.push_back(std::move(obj));

	return rawPtr;
}
