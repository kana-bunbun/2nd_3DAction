#include "GameObjectManager.h"
#include"Object/Barrier.h"
#include<memory>
#include<vector>

#include"GameObject.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	End();
}

void GameObjectManager::Init()
{

}

void GameObjectManager::End()
{
	Clear();
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& obj : m_objects) {
		if (!obj->IsActive())continue;
	
		obj->Update(deltaTime);
	}
}

void GameObjectManager::LateUpdate(float deltaTime)
{
	for (auto& obj : m_objects) {
		if (!obj->IsActive())continue;
		obj->LateUpdate(deltaTime);
	}
}

void GameObjectManager::Draw()
{
	std::vector<GameObject*>transparentIndex;
	for (auto& object:m_objects) {
		if (!object->IsActive())continue;
		if (object->IsTransparent()) {
			transparentIndex.push_back(object.get());
			continue;
		}
		object->Draw();
	}
	// 透明になるオブジェクトは後に描画する
	for (auto& object : transparentIndex) {
		if (!object->IsActive())continue;
		object->Draw();
	}
}

void GameObjectManager::CheckCollision()
{
	//// GameObjectManagerに登録されているオブジェクトを総当たりでチェックする
	//for (size_t i = 0; i < m_objects.size(); i++) {
	//	// オブジェクトの取得
	//	GameObject* objA = m_objects[i].get();

	//	// アクティブになっていなければスルー
	//	if (!objA->IsActive())continue;

	//	for (size_t j = 0; j < m_objects.size(); j++) {
	//		// オブジェクトの取得
	//		GameObject* objB = m_objects[j].get();

	//		// アクティブになっていなければスルー
	//		if (!objB->IsActive())continue;

	//		// コリジョンが未設定かどうか確認

	//		const Collision::Shape& collisionA = objA->GetCollision();
	//		const Collision::Shape& collisionB = objB->GetCollision();
	//		
	//		Collision::Result result = collisionA.CheckCollision(collisionB);
	//		// 当たっていなければスルー
	//		if (!result.isHit)continue;

	//		// 当たっていたらそれぞれのオブジェクトに衝突結果を渡す
	//		objA->ResolveCollision(*objB, result);
	//		// 法線を反転させてから渡す
	//		result.normal *= -1;
	//		objB->ResolveCollision(*objA, result);

	//	}

	//}

	// GameObjectManagerに登録されているGameObjectを総当たりでチェックする
	// 衝突判定で使用するオブジェクトの取得、衝突判定の有無をチェック
	// 確認が取れたら衝突判定の結果を取得し、各オブジェクトへ結果を返す
	for (size_t i=0; i < m_objects.size(); i++) {
		// オブジェクトの取得
		GameObject* objA = m_objects[i].get();
	
		// アクティブになっていなければスルー
		if (!objA->IsActive())continue;
		// objAのすべてのコリジョンを取得
		const auto& collisionsA = objA->GetCollisions();
		// コリジョンがなければスルー
		if (collisionsA.empty())continue;
		for (size_t j = 0; j < m_objects.size(); j++) {
			// オブジェクトの取得
			GameObject* objB = m_objects[j].get();
			// アクティブになっていなければスルー
			if (!objB->IsActive())continue;
			// objBのすべてのコリジョンを取得
			const auto& collisionsB = objB->GetCollisions();
			// コリジョンがなければスルー
			if (collisionsB.empty())continue;

			if (objA->GetCollisionTag() == GameObject::CollisionTag::Wall &&
				objB->GetCollisionTag() == GameObject::CollisionTag::Wall)continue;

			for (auto& collisionA : collisionsA) {
				// コリジョンがなければスルー
				if (!collisionA.shape)continue;
				for (auto& collisionB : collisionsB) {
					// コリジョンがなければスルー
					if (!collisionB.shape)continue;
					// 衝突判定
					Collision::Result resultA = collisionA.shape->CheckCollision(*collisionB.shape);

					// 当たっていなければスルー
					if (!resultA.isHit)continue;

					// objAの衝突後処理
					objA->ResolveCollision(*objB, collisionA, collisionB, resultA);

					// 衝突結果をコピー
					Collision::Result resultB = resultA;
					// 法線を反転
					resultB.normal *= -1;
					
					// objBの衝突後処理
					objB->ResolveCollision(*objA, collisionB, collisionA, resultB);
					

				}
			}

		}

	}

}

void GameObjectManager::Clear()
{
	for (auto& obj : m_objects) {
		obj->End();
	}
	m_objects.clear();
	m_destrpyObjects.clear();
}

void GameObjectManager::DestroObject(GameObject* obj)
{
	if (!obj)return;
	m_destrpyObjects.push_back(obj);
}

void GameObjectManager::ProcessDestroy()
{
	// 削除予定のオブジェクトがなければスルー
	if (m_destrpyObjects.empty())return;

	// 管理している全オブジェクトをチェック、削除するのでイテレータで対応
	for (auto it = m_objects.begin(); it != m_objects.end();) {
		GameObject* obj = it->get();

		// 削除フラグを用意
		bool destroy = false;

		// 削除予定リストと比較
		for (auto* target : m_destrpyObjects) {
			if (obj == target) {
				destroy = true;
				break;
			}
		}
		if (destroy) {
			obj->End();
			it = m_objects.erase(it);
		}
		else {
			// 削除予定のものがなければ次の要素をチェック
			it++;
		}
	}

	// 削除対応が終わったので削除予定リストをクリア
	m_destrpyObjects.clear();
}

const std::vector<std::unique_ptr<GameObject>>& GameObjectManager::GetObjects() const
{
	return m_objects;
}
